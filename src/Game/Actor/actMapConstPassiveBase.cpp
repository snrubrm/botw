#include "Game/Actor/actMapConst.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::act {

MapConstPassiveBase::MapConstPassiveBase(const CreateArg& arg) : MapConst(arg) {}

bool MapConstPassiveBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return MapConst::prepareInit_(heap, arg);
}

void MapConstPassiveBase::preDelete2_(const PreDeleteArg& arg) {
    MapConst::preDelete2_(arg);
}

void MapConstPassiveBase::initMaybe() {
    MapConst::initMaybe();
}

void MapConstPassiveBase::updatePositionMaybe() {
    MapConst::updatePositionMaybe();
}

void MapConstPassiveBase::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    if (mMapObject)
        ksys::map::PlacementMgr::instance()->disableObjStaticCompound(mMapObject);
}

void MapConstPassiveBase::m63() {
    MapConst::m63();
    if (mMapObject) {
        if (!mMapObject->getFlags().isOn(ksys::map::Object::Flag::_2000))
            ksys::map::PlacementMgr::instance()->enableObjStaticCompound(mMapObject);
        else if (mPhysics)
            mPhysics->sub_7100FBA9BC();
    }
}

}  // namespace uking::act
