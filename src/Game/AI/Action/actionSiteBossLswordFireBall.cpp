#include "Game/AI/Action/actionSiteBossLswordFireBall.h"

namespace uking::action {

SiteBossLswordFireBall::SiteBossLswordFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordFireBall::~SiteBossLswordFireBall() = default;

bool SiteBossLswordFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mWaitASName_s.isEmpty()) {
        mFlags.reset(Flag::Changeable);
    } else {
        playAS(mWaitASName_s.cstr(), true, 0, 0, -1.0f);
        mFlags.set(Flag::Changeable);
    }
    _64.reset(*mAppearInterval_s);
    _60 = false;
}

void SiteBossLswordFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFireBall::loadParams_() {
    getStaticParam(&mAppearInterval_s, "AppearInterval");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mIsShowChildDevice_s, "IsShowChildDevice");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getDynamicParam(&mPartsName_d, "PartsName");
}

void SiteBossLswordFireBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
