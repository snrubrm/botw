#include "Game/Actor/actMapDynamicPassive.h"
#include <basis/seadNew.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::act {

MapDynamicPassive::MapDynamicPassive(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 3;
}

ksys::act::BaseProc* MapDynamicPassive::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MapDynamicPassive(arg);
}

bool MapDynamicPassive::canWakeUp_() {
    const bool can_wake_up = Actor::canWakeUp_();
    auto* obj = mMapObject;
    if (obj) {
        if (obj->shouldSkipSpawn())
            ksys::map::PlacementMgr::instance()->disableObjStaticCompound(obj);
        else if (!can_wake_up)
            ksys::map::PlacementMgr::instance()->enableObjStaticCompound(obj);
    }
    return can_wake_up;
}

void MapDynamicPassive::m63() {
    DynamicActor::m63();
    if (mMapObject)
        ksys::map::PlacementMgr::instance()->disableObjStaticCompound(mMapObject);
}

void MapDynamicPassive::onPlacementObjReset() {
    _b90 = nullptr;
}

}  // namespace uking::act
