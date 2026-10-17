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
class Placement;
}

namespace ksys::act {
class FarActorMerge;
}  // namespace ksys::act

namespace ksys::map {

class MapProperties;
class Placement18;
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
        res::Placement* mPlacementRes;
        res::Handle mRes;
        Placement18* mP18;
        s32 _88;
        s32 _8c;
        void* _90;
    };
    KSYS_CHECK_SIZE_NX150(PlacementMapArray, 0x98);

public:
    // 0x7100d44358 (CSV PlacementMapMgr::ctor; placeholder parameter names).
    PlacementMapMgr(sead::Heap* heap, void* a, PlacementActors* actors, Placement18* p18);
    ~PlacementMapMgr();
    // 0x7100d466c8 (CSV initStaticMaps)
    void initStaticMaps(sead::Heap* heap);
    // 0x7100d461d0 / 0x7100d46424 (CSV; declaration only): the static map archive load and parse steps.
    void loadStaticMaps_();
    void parseStaticMaps_(sead::Heap* heap);

    bool isShrineOrDivineBeast() const { return mIsShrineOrDivineBeast; }
    // Read inline by ActorSystem::onBaseProcMgrCalc (name is a guess).
    MapProperties* getMapProps() const { return mMapProps; }

    PlacementMap* getMap(int idx);
    // 0x0000007100d47270
    bool isHkscResStatus3(const sead::Vector3f& pos, bool x);
    s32 getNumMaps() const { return mMaps.size(); }
    // 0x7100d474f4 (CSV postPlaceActorsRouteStuff): passes every route of every map to 0x71011190c8 (declaration only).
    void postPlaceActorsRouteStuff(void* tera_system);
    // 0x7100d475a0 (CSV routeStuff; placeholder parameter): the same loop as postPlaceActorsRouteStuff, with the
    // tera route handler 0x710111911c.
    void routeStuff(void* tera_system);
    // 0x7100d46774 / 0x7100d470dc (CSV; declaration only): the map-array pointers for the camera cell and the
    // counts of maps that still need their dynamic data.
    void updateMapArrayPtrsForPosition(s32 col, s32 row);
    void updateNeedLoadDynMapCounts(s32 x, s32 z);
    // 0x7100d46ef8 (CSV updateHkscLoadStatusesMaybe)
    void updateHkscLoadStatusesMaybe();
    void unloadMapsThatAreTooFar();
    void removeInnerData();

private:
    friend class res::CompactionMgr;
    friend class PlacementMgr;

    sead::Buffer<PlacementMap> mMaps;
    MapProperties* mMapProps;
    s32 _18;
    s32 _1c;
    PlacementMapArray mMapArray;
    act::FarActorMerge* mFarActorMerge;
    s32 mNeedLoadDynMap;
    s32 mNeedLoadDynMapPhysics;
    bool mIsShrineOrDivineBeast;
    bool mIsShrine;
};

KSYS_CHECK_SIZE_NX150(PlacementMapMgr, 0xD0);

}  // namespace ksys::map
