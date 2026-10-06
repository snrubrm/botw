#include "Game/Actor/actMapDynamicPassive.h"
#include <basis/seadNew.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::act {

MapDynamicPassive::MapDynamicPassive(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 3;
}

ksys::act::BaseProc* MapDynamicPassive::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MapDynamicPassive(arg);
}

bool MapDynamicPassive::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return DynamicActor::prepareInit_(heap, arg);
}

void MapDynamicPassive::onPreDeleteStart_(PrepareArg& arg) {
    DynamicActor::onPreDeleteStart_(arg);
}

void MapDynamicPassive::preDelete2_(const PreDeleteArg& arg) {
    DynamicActor::preDelete2_(arg);
}

void MapDynamicPassive::onEnterDelete_() {
    DynamicActor::onEnterDelete_();
}

void MapDynamicPassive::calcMaybe() {
    DynamicActor::calcMaybe();
}

void MapDynamicPassive::updatePositionMaybe() {
    DynamicActor::updatePositionMaybe();
}

void MapDynamicPassive::m73() {
    DynamicActor::m73();
}

void MapDynamicPassive::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    DynamicActor::m76(setter);
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

// NON_MATCHING: the original tests the object, the physics and the call result in that order (ours: physics, object,
// then an `eor` of the call result)
void MapDynamicPassive::initMaybe() {
    DynamicActor::initMaybe();
    auto* physics = mPhysics;
    auto* obj = mMapObject;
    const bool flag = sub_71011C5C4C();
    if (obj && physics && flag) {
        u8 type = 5;
        if (auto* link_data = obj->getLinkData()) {
            constexpr auto cLinkType = ksys::map::MapLinkDefType(0x1f);
            if (link_data->mLinksToSelf.findLinkWithType(cLinkType) ||
                link_data->findLinkWithType(cLinkType))
                type = 0xf;
        }
        physics->sub_7100FBD434(type);
    }
}

void MapDynamicPassive::onPlacementObjReset() {
    _b90 = nullptr;
}

}  // namespace uking::act
