#include "Game/AI/Action/actionRemainsWaterChaseBulletMove.h"
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

}  // namespace uking::action
