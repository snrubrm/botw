#include "Game/Actor/Action/actionRemainsWaterBulletWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

RemainsWaterBulletWait::RemainsWaterBulletWait(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterBulletWait::~RemainsWaterBulletWait() = default;

bool RemainsWaterBulletWait::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterBulletWait::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void RemainsWaterBulletWait::leave_() {
    RemainsWaterBulletAction::leave_();
}

void RemainsWaterBulletWait::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mMaxChaseAngle_s, "MaxChaseAngle");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mChaseRate_s, "ChaseRate");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterBulletWait::calc_() {
    RemainsWaterBulletAction::calc_();
}

// NON_MATCHING: target/position stack slots and velocity scaling stores differ.
void RemainsWaterBulletWait::m32() {
    auto* body = mActor->getMainBody();
    if (!body || !body->isAddedToWorld())
        return;
    sead::Vector3f target;
    sub_71002325BC(&target);
    if (target.isNan())
        target = mActor->getMtx().getTranslation();
    sead::Vector3f position;
    sead::Vector3f velocity;
    body->getPosition(&position);
    body->getLinearVelocity(&velocity);
    if (velocity.isNan())
        velocity.set(0.0f, 0.0f, 0.0f);
    else
        velocity *= 1.0f / 30.0f;
    sead::Vector3f direction = target - position;
    if (direction.length() > 0.0f) {
        const f32 length = direction.normalize();
        direction *= length > *mMaxSpeed_s ? *mMaxSpeed_s : length;
    }
    ksys::VFR::lerp(&velocity, direction, *mChaseRate_s);
    body->setLinearVelocity(velocity * 30.0f, sead::Mathf::epsilon());
}

}  // namespace uking::action
