#include "Game/AI/Action/actionNotStopXLinkWithDemoVisibleOff.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

NotStopXLinkWithDemoVisibleOff::NotStopXLinkWithDemoVisibleOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NotStopXLinkWithDemoVisibleOff::~NotStopXLinkWithDemoVisibleOff() = default;

void NotStopXLinkWithDemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    if (auto* body = actor->getPhysicsMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, true);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115CE44("Root");
}

void NotStopXLinkWithDemoVisibleOff::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115D0AC();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
}

}  // namespace uking::action
