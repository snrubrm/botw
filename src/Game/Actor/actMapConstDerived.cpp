#include "Game/Actor/actMapConst.h"
#include <basis/seadNew.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::act {

MapConstActiveOrMergedDungeonParts::MapConstActiveOrMergedDungeonParts(const CreateArg& arg)
    : MapConst(arg) {}

bool MapConstActiveOrMergedDungeonParts::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return MapConst::prepareInit_(heap, arg);
}

void MapConstActiveOrMergedDungeonParts::preDelete2_(const PreDeleteArg& arg) {
    MapConst::preDelete2_(arg);
}

void MapConstActiveOrMergedDungeonParts::initMaybe() {
    MapConst::initMaybe();
}

void MapConstActiveOrMergedDungeonParts::updatePositionMaybe() {
    MapConst::updatePositionMaybe();
}

void MapConstActiveOrMergedDungeonParts::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    if (mMapObject)
        ksys::map::PlacementMgr::instance()->disableObjStaticCompound(mMapObject);
}

bool MapConstActiveOrMergedDungeonParts::canWakeUp_() {
    const bool can_wake_up = Actor::canWakeUp_();
    auto* obj = mMapObject;
    if (obj) {
        if (obj->shouldSkipSpawn())
            ksys::map::PlacementMgr::instance()->disableObjStaticCompound(obj);
        else if (can_wake_up)
            ksys::map::PlacementMgr::instance()->enableObjStaticCompound(obj);
    }
    return can_wake_up;
}

void MapConstActiveOrMergedDungeonParts::m63() {
    MapConst::m63();
    if (mMapObject) {
        if (!mMapObject->getFlags().isOn(ksys::map::Object::Flag::_2000))
            ksys::map::PlacementMgr::instance()->enableObjStaticCompound(mMapObject);
        else if (mPhysics)
            mPhysics->sub_7100FBA9BC();
    }
}

}  // namespace uking::act
