#include "Game/AI/AI/aiSiteBossLswordFireBallRoot.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SiteBossLswordFireBallRoot::SiteBossLswordFireBallRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossLswordFireBallRoot::~SiteBossLswordFireBallRoot() = default;

bool SiteBossLswordFireBallRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _e8.search(model, "Eyeball");
    else
        _e8.getKey().reset();
    return true;
}

void SiteBossLswordFireBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備");
    _d8 = *mTargetPos_d;
    _98 = false;

    s32 rate_a;
    s32 rate_b;
    switch (_9c) {
    case 0:
        rate_a = 43;
        rate_b = 43;
        break;
    case 1:
        rate_a = 13;
        rate_b = 43;
        break;
    default:
        rate_a = 43;
        rate_b = 13;
        break;
    }

    const u32 r = sead::GlobalRandom::instance()->getU32(100);
    if (r < rate_a)
        _9c = 1;
    else
        _9c = r < rate_a + rate_b ? 2 : 0;
    _a0 = 0;
    _a4 = 0;
}

void SiteBossLswordFireBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossLswordFireBallRoot::loadParams_() {
    getStaticParam(&mPredictPosRate_s, "PredictPosRate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mYOffset_s, "YOffset");
    getStaticParam(&mIsThrowChildDevice_s, "IsThrowChildDevice");
    getStaticParam(&mIsNeedCreateChildDevice_s, "IsNeedCreateChildDevice");
    getStaticParam(&mBindPosOffset_s, "BindPosOffset");
    getDynamicParam(&mThrowActorName_d, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
