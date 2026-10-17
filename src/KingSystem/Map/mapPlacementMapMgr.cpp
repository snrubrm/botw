#include "KingSystem/Map/mapPlacementMapMgr.h"
#include <time/seadTickTime.h>
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Resource/resPlacement.h"
#include "KingSystem/Map/mapMapProperties.h"
#include "KingSystem/ActorSystem/actFarActorMerge.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {
// 0x710111911c (declaration only): the second route handler, next to 0x71011190c8 in teraSystem.h.
void sub_710111911C(void* tera_system, void* route);
}  // namespace ksys::tera

namespace ksys::map {

PlacementMap* PlacementMapMgr::getMap(int idx) {
    return &mMaps[idx];
}

PlacementMapMgr::~PlacementMapMgr() {
    removeInnerData();

    // The maps are a new[] array, so this calls ~PlacementMap on every element through the array
    // cookie before freeing it.
    mMaps.freeBuffer();

    mMapArray.mMaps.freeBuffer();
    mMapArray.mPtrs.freeBuffer();

    if (mMapArray._90) {
        operator delete[](mMapArray._90);
        mMapArray._90 = nullptr;
        mMapArray._88 = 0;
    }

    if (mFarActorMerge)
        delete mFarActorMerge;
}

// NON_MATCHING: the original compares `pz <= 7999` first and places the `return x` block before the index
// computation; ours tests `px` first (instcombine orders the two compares by definition order).
bool PlacementMapMgr::isHkscResStatus3(const sead::Vector3f& pos, bool x) {
    int col, row;
    if (mMapProps->m0() == 1 || mMapProps->m0() == 2) {
        row = 4;
        col = 5;
    } else {
        const int px = int(pos.x) + 5000;
        const int pz = int(pos.z) + 4000;
        if (!(pz <= 7999 && px <= 9999))
            return x;
        col = px / 1000;
        row = pz / 1000;
        if ((col | row) < 0)
            return x;
    }
    return mMaps[u8(row + col * 8)].isDynamicLoaded(pos);
}

// NON_MATCHING: same logic, but clang keeps one pointer induction variable in the sort's inner loops where the
// original keeps an index and a byte offset (576 vs 632 bytes); the two column/row selects are also 64-bit here.
void PlacementMapMgr::updateMapArrayPtrsForPosition(s32 col, s32 row) {
    const s32 c = mIsShrineOrDivineBeast == 0 ? col : 5;
    const s32 r = mIsShrineOrDivineBeast == 0 ? row : 4;
    mMapArray.mMaps.clear();

    // The maps are stored column-major: 8 rows of 0x400 bytes for each of the 10 columns.
    for (s32 i = 0; i < 10; ++i) {
        for (s32 j = 0; j < 8; ++j) {
            auto& map = mMaps[i * 8 + j];
            map.mDistanceToCurrentMapUnit =
                sead::Mathi::max(sead::Mathi::abs(c - i), sead::Mathi::abs(r - j));
            mMapArray.mMaps.pushBack(&map);
        }
    }

    for (s32 i = 0; i < mMapProps->isOpenWorld(); ++i) {
        auto& map = mMaps[_18 + i];
        map.mDistanceToCurrentMapUnit = mMapProps->m9(i) == 1 ? 1 : -1;
        mMapArray.mMaps.pushBack(&map);
    }

    mMapArray.mMaps.sort([](const PlacementMap* a, const PlacementMap* b) {
        return a->mDistanceToCurrentMapUnit - b->mDistanceToCurrentMapUnit;
    });
}

// NON_MATCHING: Buffer indexing and temporary strings use different stack allocation.
void PlacementMapMgr::loadStaticMaps_() {
    // The release build keeps the timing read after dropping its debug output.
    sead::TickTime start;
    sead::FixedSafeString<128> path;
    sead::FixedSafeString<64> map_type;
    mMapProps->getMapType(&map_type);
    path.format("Placement/%s.bplacement", map_type.cstr());
    for (s64 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        if (map.mStaticMapLoaded)
            continue;
        bool in_archive = false;
        if (mMapArray.mPlacementRes) {
            for (s64 j = 0; j < mMapArray.mPlacementRes->getNumEntries(); ++j) {
                if (map.mMubinPath == sead::SafeString(mMapArray.mPlacementRes->getEntryName(j))) {
                    in_archive = true;
                    break;
                }
            }
        }
        if (!in_archive)
            map.loadStaticMap_(false);
    }
}

// NON_MATCHING: Buffer indexing and temporary strings use different stack allocation.
void PlacementMapMgr::parseStaticMaps_(sead::Heap* heap) {
    // The release build keeps the timing read after dropping its debug output.
    sead::TickTime start;
    for (s64 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        if (map.mStaticMapLoaded)
            continue;
        u8* data = nullptr;
        if (mMapArray.mPlacementRes) {
            for (s64 j = 0; j < mMapArray.mPlacementRes->getNumEntries(); ++j) {
                if (map.mMubinPath == sead::SafeString(mMapArray.mPlacementRes->getEntryName(j))) {
                    data = mMapArray.mPlacementRes->getEntryData(j);
                    break;
                }
            }
            if (!data) {
                sead::FixedSafeString<128> path;
                sead::FixedSafeString<64> map_type;
                mMapProps->getMapType(&map_type);
                path.format("Placement/%s.bplacement", map_type.cstr());
            }
        }
        map.parseStaticMap_(heap, data);
    }
    if (mMapArray.mP18)
        mMapArray.mP18->x(heap);
}

void PlacementMapMgr::initStaticMaps(sead::Heap* heap) {
    loadStaticMaps_();
    parseStaticMaps_(heap);

    sead::FixedSafeString<64> map_type;
    mMapProps->getMapType(&map_type);
    mFarActorMerge->sub_710124ABC0(map_type, heap);
}

void PlacementMapMgr::updateNeedLoadDynMapCounts(s32 x, s32 z) {
    s32 count = 0;
    s32 physics_count = 0;
    for (s32 i = 0; i < mMapArray.mMaps.size(); ++i) {
        auto* map = mMapArray.mMaps[i];
        if (map->mFolderAndFile.findIndex("_DistanceView") == -1 &&
            map->mMubinPath.cstr()[0] != sead::SafeString::cNullChar &&
            map->mDistanceToCurrentMapUnit < 2) {
            if (map->mInitStatus < PlacementMap::InitStatus::DynamicLoaded)
                ++count;

            if (map->mInitStatus == PlacementMap::InitStatus::DynamicLoaded) {
                for (s32 j = 0; j < 4; ++j) {
                    if (map->x_1(j, f32(x), f32(z)) &&
                        map->mRes[j].mStatus < PlacementMap::HkscRes::Status::_2)
                        ++physics_count;
                }
            }
        }
    }
    mNeedLoadDynMap = count;
    mNeedLoadDynMapPhysics = physics_count;
}

void PlacementMapMgr::updateHkscLoadStatusesMaybe() {
    auto* placement_mgr = PlacementMgr::instance();
    for (s32 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        if (map.mInitStatus == PlacementMap::InitStatus::_4 && !placement_mgr->someFlagCheck()) {
            map.x_9();
            map.mInitStatus = PlacementMap::InitStatus::_5;
        }

        for (s32 j = 0; j < 4; ++j) {
            auto& res = map.mRes[j];
            if (res.mStatus == PlacementMap::HkscRes::Status::_2) {
                if (map.doSomethingStaticCompound(j))
                    res.mStatus = PlacementMap::HkscRes::Status::_3;
            }
            if (res.mStatus == PlacementMap::HkscRes::Status::_4) {
                if (map.staticCompoundStuff(j, false))
                    res.mStatus = PlacementMap::HkscRes::Status::_5;
            }
        }
    }
}

void PlacementMapMgr::removeInnerData() {
    for (s32 i = 0; i < mMaps.size(); ++i) {
        mMaps[i].cleanupPhysics();
        if (mMaps[i].mDynamicGroupIdx >= 0)
            mMaps[i].unload();
    }
    mFarActorMerge->cleanup();
    mNeedLoadDynMap = 0;
    mNeedLoadDynMapPhysics = 0;
}

void PlacementMapMgr::unloadMapsThatAreTooFar() {
    for (s32 i = 0; i < mMapArray.mMaps.size(); ++i) {
        auto* map = mMapArray.mMaps.at(i);
        if (map->mDistanceToCurrentMapUnit >= 2 && map->mDynamicGroupIdx >= 0) {
            map->unload();
            map->mInitStatus = PlacementMap::InitStatus::StaticLoaded;
        }
    }
}

void PlacementMapMgr::routeStuff(void* tera_system) {
    for (s32 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        for (s32 j = 0; j < map.mNumRoutes; ++j)
            tera::sub_710111911C(tera_system, map.mRoutes[j]);
    }
}

void PlacementMapMgr::postPlaceActorsRouteStuff(void* tera_system) {
    for (s32 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        for (s32 j = 0; j < map.mNumRoutes; ++j)
            tera::sub_71011190C8(tera_system, map.mRoutes[j]);
    }
}

}  // namespace ksys::map
