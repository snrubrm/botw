#include "Game/AI/Action/actionKnockBackShock.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

KnockBackShock::KnockBackShock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KnockBackShock::~KnockBackShock() = default;

bool KnockBackShock::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: stack layout (the original keeps the gravity / up / direction vectors in one stack slot and
// the up vector in registers until it is passed by reference)
void KnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f velocity = actor->getVelocity();
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f dir = sead::Vector3f::zero;
    sub_71005E2318(&dir, actor, sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr()));
    velocity += dir * *mHitImpactForce_s;

    sead::Vector3f up;
    {
        sead::Vector3f gravity;
        sub_710072DC50(&gravity, actor);
        up = -gravity;
    }
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    ksys::util::sub_71011EFA00(&velocity, velocity, up);

    sead::Vector3f axis = velocity;
    const f32 speed = axis.normalize();
    sub_710072C1B4(controller, axis);
    sub_7100737708(controller, speed);
}

void KnockBackShock::leave_() {
    ksys::act::ai::Action::leave_();
}

void KnockBackShock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mVelReduceOnGround_s, "VelReduceOnGround");
}

void KnockBackShock::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (isBgGroundHit(actor, false))
        sub_7100737C0C(controller, *mVelReduceOnGround_s, -sead::Vector3f::ey);
    else
        sub_7100737C0C(controller, *mVelReduce_s, -sead::Vector3f::ey);
}

}  // namespace uking::action
