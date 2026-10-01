#include "Game/AI/AI/aiTargetLostCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::ai {

TargetLostCheck::TargetLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetLostCheck::~TargetLostCheck() = default;

bool TargetLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time = *mLostTimer_s;
    const int time2 = time * 1.1f;
    _54 = sead::Mathi::min(time, time2);
    _58 = sead::Mathi::max(time, time2);

    s32 timer = _54;
    if (_58 != _54)
        timer = sead::GlobalRandom::instance()->getS32Range(_54, _58);
    _50 = timer;

    changeChild("発見行動", params);
}

void TargetLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mIsLostByScaffold_s, "IsLostByScaffold");
    getStaticParam(&mIsLostByTeached_s, "IsLostByTeached");
}

bool TargetLostCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetLostCheck::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
