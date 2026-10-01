#include "Game/AI/Action/actionEventDisableContactLayerTrigger.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

EventDisableContactLayerTrigger::EventDisableContactLayerTrigger(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisableContactLayerTrigger::~EventDisableContactLayerTrigger() = default;

bool EventDisableContactLayerTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventDisableContactLayerTrigger::oneShot_() {
    if (auto* body = mActor->getMainBody())
        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    return true;
}

void EventDisableContactLayerTrigger::loadParams_() {
    getDynamicParam(&mContactType_d, "ContactType");
}

}  // namespace uking::action
