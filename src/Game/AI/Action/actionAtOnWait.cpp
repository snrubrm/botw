#include "Game/AI/Action/actionAtOnWait.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

AtOnWait::AtOnWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool AtOnWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AtOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AtOnWait::leave_() {
    auto* set = mActor->getRigidBodyByName(sub_71007A24BC()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            sub_71007A2D34(body);
    }
}

void AtOnWait::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
}

void AtOnWait::calc_() {
    auto* actor = mActor;
    auto* set = actor->getRigidBodyByName(sub_71007A24BC()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->changePositionAndRotation(actor->getMtx(), sead::Mathf::epsilon());
    }
}

}  // namespace uking::action
