#include "Game/AI/Action/actionAreaRecreateActorAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AreaRecreateActorAction::AreaRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaRecreateActorAction::~AreaRecreateActorAction() {
    _38.freeBuffer();
}

bool AreaRecreateActorAction::init_(sead::Heap* heap) {
    _38.tryAllocBuffer(2, heap);
    if (!_38.isBufferReady())
        return false;
    _38[0]._0 = ksys::phys::ContactLayer::SensorObject;
    _38[1]._0 = ksys::phys::ContactLayer::SensorSmallObject;
    return true;
}

bool AreaRecreateActorAction::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!mActor)
        return true;
    mActor->sub_71011DA808(accessor);
    return false;
}

}  // namespace uking::action
