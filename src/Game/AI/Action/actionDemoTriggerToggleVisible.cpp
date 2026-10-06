#include "Game/AI/Action/actionDemoTriggerToggleVisible.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

DemoTriggerToggleVisible::DemoTriggerToggleVisible(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoTriggerToggleVisible::~DemoTriggerToggleVisible() = default;

bool DemoTriggerToggleVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DemoTriggerToggleVisible::oneShot_() {
    auto* actor = mActor;
    if (auto* body = actor->getPhysicsMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    }
    if (*mIsVisible_d) {
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        actor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
        if (*mIsXLinkHandling_d) {
            if (auto* xlink = actor->getXLink()) {
                xlink->toggle(true);
                xlink->_cc.set(4);
            }
        }
        if (*mIsClothHandling_d) {
            if (auto* physics = actor->getPhysics()) {
                physics->clothVisibleStuff();
                physics->clothVisibleStuff_0(1);
            }
        }
    } else {
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        actor->setFlag(ksys::act::Actor::ActorFlag::_2b, true);
        if (*mIsXLinkHandling_d) {
            if (auto* xlink = actor->getXLink()) {
                xlink->sleep(1);
                xlink->_cc.reset(4);
            }
        }
    }
    return true;
}

void DemoTriggerToggleVisible::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
    getDynamicParam(&mIsXLinkHandling_d, "IsXLinkHandling");
    getDynamicParam(&mIsClothHandling_d, "IsClothHandling");
}

}  // namespace uking::action
