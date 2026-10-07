#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Map/mapPlacementMap.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class CompactionMgr;
}

namespace ksys::map {

class MapProperties;
class Placement18;
class FarActorMerge;
class PlacementActors;

class PlacementMap;

/* NOT WORKING */
class PlacementMapMgr {
    /* NOT WORKING */
    class PlacementMapArray {
    public:
        PlacementMapArray() = default;
        ~PlacementMapArray() = default;

        sead::PtrArray<PlacementMap> mMaps;
        sead::PtrArray<PlacementMap> mPtrs;
        PlacementActors* mPa;
        s64 _28;
        res::Handle mRes;
        Placement18* mP18;
        s32 _88;
        s32 _8c;
        void* _90;
    };
    KSYS_CHECK_SIZE_NX150(PlacementMapArray, 0x98);

public:
    PlacementMapMgr() = default;
    ~PlacementMapMgr();

    bool isShrineOrDivineBeast() const { return mIsShrineOrDivineBeast; }

    PlacementMap* getMap(int idx);
    // 0x0000007100d47270
    bool isHkscResStatus3(const sead::Vector3f& pos, bool x);
    s32 getNumMaps() const { return mMaps.size(); }
    // 0x7100d474f4 (CSV postPlaceActorsRouteStuff): passes every route of every map to 0x71011190c8 (declaration only).
    void postPlaceActorsRouteStuff(void* tera_system);
    // 0x7100d46ef8 (CSV updateHkscLoadStatusesMaybe)
    void updateHkscLoadStatusesMaybe();

private:
    friend class res::CompactionMgr;
    friend class PlacementMgr;

    sead::Buffer<PlacementMap> mMaps;
    MapProperties* mMapProps;
    s32 _18;
    s32 _1c;
    PlacementMapArray mMapArray;
    FarActorMerge* mFarActorMerge;
    s32 mNeedLoadDynMap;
    s32 mNeedLoadDynMapPhysics;
    bool mIsShrineOrDivineBeast;
    bool mIsShrine;
};

KSYS_CHECK_SIZE_NX150(PlacementMapMgr, 0xD0);

}  // namespace ksys::map
