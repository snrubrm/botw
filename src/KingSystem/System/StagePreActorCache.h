#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Map/mapMapProperties.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::gfx {
class ForestRenderer;
}

namespace ksys::util {
class DualHeap;
}

namespace ksys::map {
class LazyTraverseList;
class Placement18;
class PlacementActors;
class PlacementMapMgr;
}  // namespace ksys::map

namespace ksys {

// TODO
class StagePreActorCache : public map::MapProperties {
    SEAD_SINGLETON_DISPOSER(StagePreActorCache)
    StagePreActorCache();

public:
    void init(sead::Heap* heap, sead::Heap* heap2);
    void reset();
    void loadMaps(const sead::SafeString& map_type);
    bool isMapTypeEqual(const sead::SafeString& map_type) const;

    int m0() override;
    void getMapType(sead::BufferedSafeString* out) override;
    bool m2(sead::BufferedSafeString* out) override;
    bool getMapName(sead::BufferedSafeString* out, int x, int z) override;
    void m4(int* x, int* z, const sead::SafeString& name) override;

    map::LazyTraverseList* getObjects() const { return mObjects; }
    map::Placement18* getPlacement18() const { return mPlacement18; }
    auto* getForestRenderer() { return mForestRenderer; }

private:
    map::PlacementActors* mPlacementActors = nullptr;
    map::PlacementMapMgr* mPlacementMapMgr = nullptr;
    map::Placement18* mPlacement18 = nullptr;
    map::LazyTraverseList* mObjects = nullptr;
    gfx::ForestRenderer* mForestRenderer = nullptr;
    util::DualHeap* mHeap = nullptr;
    util::DualHeap* mForestRendererHeap = nullptr;
    sead::Heap* mHeap2 = nullptr;
    sead::FixedSafeString<64> mMapType;
    bool _c0 = false;
};
KSYS_CHECK_SIZE_NX150(StagePreActorCache, 0xc8);

}  // namespace ksys
