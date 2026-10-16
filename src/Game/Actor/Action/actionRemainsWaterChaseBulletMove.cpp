#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Action/actionRemainsWaterChaseBulletMove.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Action/actionBoomerangMove.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

RemainsWaterChaseBulletMove::RemainsWaterChaseBulletMove(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterChaseBulletMove::~RemainsWaterChaseBulletMove() = default;

bool RemainsWaterChaseBulletMove::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterChaseBulletMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mWeakChaseTimer_s > 0.0f) {
        _114 = true;
        _f0.mTimer = ksys::Timer(*mWeakChaseTimer_s, *mWeakChaseTimer_s);
    } else {
        _114 = false;
    }

    RemainsWaterBulletAction::enter_(params);

    _108 = *mBaseTargetOffset_s;
    _108.x += mBaseTargetRandOffset_s->x * sead::GlobalRandom::instance()->getF32();
    _108.y += mBaseTargetRandOffset_s->y * sead::GlobalRandom::instance()->getF32();
    _108.z += mBaseTargetRandOffset_s->z * sead::GlobalRandom::instance()->getF32();
}

void RemainsWaterChaseBulletMove::leave_() {
    RemainsWaterBulletAction::leave_();
}

void RemainsWaterChaseBulletMove::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mBaseChaseSpd_s, "BaseChaseSpd");
    getStaticParam(&mMaxChaseSpd_s, "MaxChaseSpd");
    getStaticParam(&mChaseSpdRate_s, "ChaseSpdRate");
    getStaticParam(&mChaseAngleRate_s, "ChaseAngleRate");
    getStaticParam(&mDepthOffset_s, "DepthOffset");
    getStaticParam(&mMaxPredictFrame_s, "MaxPredictFrame");
    getStaticParam(&mMinPredictFrame_s, "MinPredictFrame");
    getStaticParam(&mStartPredictDist_s, "StartPredictDist");
    getStaticParam(&mEndPredictDist_s, "EndPredictDist");
    getStaticParam(&mWeakChaseTimer_s, "WeakChaseTimer");
    getStaticParam(&mBaseTargetOffset_s, "BaseTargetOffset");
    getStaticParam(&mBaseTargetRandOffset_s, "BaseTargetRandOffset");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterChaseBulletMove::calc_() {
    RemainsWaterBulletAction::calc_();
    if (!_114)
        return;

    _f0.sub_7100D3BCE4();
    if (_f0.mTimer.value <= sead::Mathf::epsilon())
        _114 = false;
}

void RemainsWaterChaseBulletMove::m32() {
    if (auto* body = mActor->getMainBody()) {
        if (body->isAddedToWorld()) {
            sead::Vector3f velocity;
            if (sub_710023357C(&velocity))
                body->setLinearVelocity(velocity);
        }
    }
}

// NON_MATCHING: stack layout (the speed and its target are stack slots at the frame top) and float registers.
bool RemainsWaterChaseBulletMove::sub_710023357C(sead::Vector3f* out) {
    ksys::act::acc::PlayerBase player;
    if (!player.getPlayerFromPlayerInfo())
        return false;

    const sead::Vector3f& player_velocity = player.getVelocity();
    const f32 player_speed = sead::Vector2f(player_velocity.x, player_velocity.z).length();
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return false;
    sead::Vector3f target;
    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    if (velocity.isNan())
        return false;
    velocity *= 1.0f / 30.0f;

    const sead::Vector3f pos = actor->getMtx().getTranslation();
    if (!sub_71002338D4(&target))
        return false;

    sead::Vector3f dir = target - pos;
    dir.normalize();
    f32 angle_rate = *mChaseAngleRate_s;
    if (_114) {
        const f32 t = sead::Mathf::clamp(_f0.mTimer.value / *mWeakChaseTimer_s, 0.0f, 0.99f);
        angle_rate *= 1.0f - t;
    }
    f32 speed = 0.0f;
    if (velocity == sead::Vector3f(0, 0, 0)) {
        velocity = dir;
    } else {
        speed = velocity.normalize();
        sub_71000CB074(&velocity, &dir, angle_rate);
    }
    const f32 max_speed = sead::Mathf::min(player_speed + *mBaseChaseSpd_s, *mMaxChaseSpd_s);
    const f32 diff = sead::Mathf::abs(max_speed - speed);
    ksys::VFR::lerp(&speed, max_speed, *mChaseSpdRate_s, diff * 0.3f, diff * 0.1f);
    velocity *= speed;
    *out = velocity * 30.0f;
    return true;
}

}  // namespace uking::action
