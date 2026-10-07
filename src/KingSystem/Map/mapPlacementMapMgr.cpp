#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Map/mapMapProperties.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::map {

PlacementMap* PlacementMapMgr::getMap(int idx) {
    return &mMaps[idx];
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

void PlacementMapMgr::postPlaceActorsRouteStuff(void* tera_system) {
    for (s32 i = 0; i < mMaps.size(); ++i) {
        auto& map = mMaps[i];
        for (s32 j = 0; j < map.mNumRoutes; ++j)
            tera::sub_71011190C8(tera_system, map.mRoutes[j]);
    }
}

}  // namespace ksys::map
