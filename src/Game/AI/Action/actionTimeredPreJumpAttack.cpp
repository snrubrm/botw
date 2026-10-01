#include "Game/AI/Action/actionTimeredPreJumpAttack.h"
#include "KingSystem/System/Timer.h"
#include "random/seadGlobalRandom.h"

namespace uking::action {

TimeredPreJumpAttack::TimeredPreJumpAttack(const InitArg& arg) : PreJumpAttack(arg) {}

TimeredPreJumpAttack::~TimeredPreJumpAttack() = default;

bool TimeredPreJumpAttack::init_(sead::Heap* heap) {
    return PreJumpAttack::init_(heap);
}

// NON_MATCHING: the original loads the two params before the GlobalRandom instance (scheduling)
void TimeredPreJumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PreJumpAttack::enter_(params);
    _a8 = *mTime_s + s32(sead::GlobalRandom::instance()->getU32(*mTimeRand_s));
    mFlags.set(Flag::Changeable);
}

void TimeredPreJumpAttack::leave_() {
    PreJumpAttack::leave_();
}

void TimeredPreJumpAttack::loadParams_() {
    PreJumpAttack::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void TimeredPreJumpAttack::calc_() {
    PreJumpAttack::calc_();
    ksys::Timer::update(&_a8, -1.0f);
    if (_a8 < 0.0f)
        setFinished();
}

}  // namespace uking::action
