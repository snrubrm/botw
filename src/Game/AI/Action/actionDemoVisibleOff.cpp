#include "Game/AI/Action/actionDemoVisibleOff.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

DemoVisibleOff::DemoVisibleOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOff::~DemoVisibleOff() = default;

void DemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    if (!ksys::evt::Manager::instance()->sub_7100DB20D0()) {
        if (auto* xlink = actor->getXLink()) {
            xlink->sleep(ksys::xlink::XLink::MaskBit::_1);
            xlink->_cc.reset(4);
        }
    }
    if (auto* body = actor->getPhysicsMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, true);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115CE44("Root");
}

void DemoVisibleOff::leave_() {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    if (!ksys::evt::Manager::instance()->sub_7100DB20D0()) {
        if (auto* xlink = actor->getXLink()) {
            xlink->toggle(ksys::xlink::XLink::MaskBit::_1);
            xlink->_cc.set(4);
        }
    }
    if (auto* physics = mActor->getPhysics()) {
        physics->clothVisibleStuff();
        physics->clothVisibleStuff_0(1);
    }
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115D0AC();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
}

}  // namespace uking::action
