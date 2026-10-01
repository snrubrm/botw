#include "Game/AI/AI/aiTargetPosLostCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetPosLostCheck::TargetPosLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosLostCheck::~TargetPosLostCheck() = default;

bool TargetPosLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time_a = *mLostTimer_s;
    const int time_b = *mLostTimer_s * 1.1f;
    _64 = sead::Mathi::min(time_a, time_b);
    _68 = sead::Mathi::max(time_a, time_b);
    s32 time = _64;
    if (_68 != _64)
        time = sead::GlobalRandom::instance()->getS32Range(_64, _68);
    _60 = time;

    ksys::act::ai::InlineParamPack params_;
    params_.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("発見行動", &params_);
}

void TargetPosLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetPosLostCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
