#include "Game/AI/Action/actionLastBossPostNormalWarp.h"
#include "math/seadMathCalcCommon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossPostNormalWarp::LastBossPostNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossPostNormalWarp::~LastBossPostNormalWarp() = default;

bool LastBossPostNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossPostNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossPostNormalWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossPostNormalWarp::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mNoCryAnime_s, "NoCryAnime");
    getStaticParam(&mIsTurnToTarget_s, "IsTurnToTarget");
    getStaticParam(&mIsCheckDistFromTarget_s, "IsCheckDistFromTarget");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsKeepDisableDraw_d, "IsKeepDisableDraw");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossPostNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

bool LastBossPostNormalWarp::isFinished() const {
    if ((!_70 && isFinishedAS(0, 0) && *mWaitTime_s <= 0.0f) ||
        (_70 && _78 <= sead::Mathf::epsilon())) {
        if (!*mIsCheckDistFromTarget_s)
            return true;
        if ((mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f)
            return false;
        return true;
    }
    return false;
}

bool LastBossPostNormalWarp::isFailed() const {
    if ((!_70 && isFinishedAS(0, 0) && *mWaitTime_s <= 0.0f) || _78 <= sead::Mathf::epsilon()) {
        if (*mIsCheckDistFromTarget_s &&
            (mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f) {
            return true;
        }
    }
    return false;
}

}  // namespace uking::action
