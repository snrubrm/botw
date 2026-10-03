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
    velocity.setScaleAdd(*mHitImpactForce_s, dir, velocity);

    ksys::util::sub_71011EFA00(&velocity, velocity, getUpDir(actor));

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
