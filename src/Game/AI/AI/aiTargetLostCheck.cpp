#include "Game/AI/AI/aiTargetLostCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

TargetLostCheck::TargetLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetLostCheck::~TargetLostCheck() = default;

bool TargetLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// inline-only in the original; name is a guess: the random timer reset appears inlined in enter_ and
// three times in calc_ (cases 2/4, and the false branches of cases 3/5).
void TargetLostCheck::resetTimer() {
    s32 time = _54;
    if (_58 != _54)
        time = sead::GlobalRandom::instance()->getS32Range(_54, _58);
    _50 = time;
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

void TargetLostCheck::calc_() {
    f32& timer = _50;

    if (sub_71005D8F28(mActor)) {
        switch (sub_71005D9744(mActor)) {
        case 2:
        case 4:
            resetTimer();
            break;
        case 3:
            if (*mIsLostByScaffold_s)
                ksys::Timer::update(&timer, -1.0f);
            else
                resetTimer();
            break;
        case 5:
            if (*mIsLostByTeached_s)
                ksys::Timer::update(&timer, -1.0f);
            else
                resetTimer();
            break;
        default:
            ksys::Timer::update(&timer, -1.0f);
            break;
        }
    } else {
        ksys::Timer::update(&timer, -1.0f);
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && child->isChangeable() && timer <= 0.0f)
        setFailed();
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
