#include "Game/AI/Action/actionSiteBossLswordThrowFireBall.h"

namespace uking::action {

// NON_MATCHING: the original runs the 21-entry array loop with a byte-offset counter from `this`
// (x21 += 0x68) instead of an element pointer
SiteBossLswordThrowFireBall::SiteBossLswordThrowFireBall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordThrowFireBall::~SiteBossLswordThrowFireBall() = default;

bool SiteBossLswordThrowFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordThrowFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordThrowFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordThrowFireBall::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mFireBallAng_s, "FireBallAng");
    getStaticParam(&mIsThrowAll_s, "IsThrowAll");
    getStaticParam(&mThrowASName_s, "ThrowASName");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getDynamicParam(&mIsThrowChildDevice_d, "IsThrowChildDevice");
    getDynamicParam(&mPartsName_d, "PartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SiteBossLswordThrowFireBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
