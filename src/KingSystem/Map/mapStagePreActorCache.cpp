#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Graphics/gfxForestRenderer.h"
#include "KingSystem/Map/mapLazyTraverseList.h"
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::map {

SEAD_SINGLETON_DISPOSER_IMPL(StagePreActorCache)

StagePreActorCache::StagePreActorCache() = default;

void StagePreActorCache::init(sead::Heap* heap, sead::Heap* heap2) {
    mHeap = util::DualHeap::create(0x2800000, "StagePreActorCache", heap, heap2, 8,
                                   sead::Heap::cHeapDirection_Forward, false);
    mForestRendererHeap = util::DualHeap::create(0x1400000, "ForestRenderer", heap, heap2, 8,
                                                 sead::Heap::cHeapDirection_Forward, false);
    mHeap->enableLock(true);
    mForestRendererHeap->enableLock(true);
    mHeap2 = heap2;
}

void StagePreActorCache::reset() {
    delete mPlacementActors;
    delete mPlacement18;
    delete mPlacementMapMgr;
    delete mObjects;
    delete mForestRenderer;
    mForestRenderer = nullptr;
}

bool StagePreActorCache::isMapTypeEqual(const sead::SafeString& map_type) const {
    if (_c0)
        return false;
    return map_type == mMapType;
}

int StagePreActorCache::m0() {
    return 0;
}

void StagePreActorCache::getMapType(sead::BufferedSafeString* out) {
    out->copy(mMapType);
}

bool StagePreActorCache::m2(sead::BufferedSafeString* out) {
    return false;
}

bool StagePreActorCache::getMapName(sead::BufferedSafeString* out, int x, int z) {
    out->format("%c-%d/%c-%d", x + 'A', z + 1, x + 'A', z + 1);
    return true;
}

void StagePreActorCache::m4(int* x, int* z, const sead::SafeString& name) {
    *x = name.at(0) - 'A';
    *z = name.at(2) - '1';
}

}  // namespace ksys::map
