#include "Game/AI/Action/actionWizzrobeVisibleWalk.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

WizzrobeVisibleWalk::WizzrobeVisibleWalk(const InitArg& arg) : LevelFlyMove(arg) {}

WizzrobeVisibleWalk::~WizzrobeVisibleWalk() = default;

bool WizzrobeVisibleWalk::init_(sead::Heap* heap) {
    return LevelFlyMove::init_(heap);
}

void WizzrobeVisibleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    _168 = ksys::Timer(*mFailMoveTimer_s, *mFailMoveTimer_s);
    LevelFlyMove::enter_(params);
    _174 = -1.0f;
}

void WizzrobeVisibleWalk::leave_() {
    LevelFlyMove::leave_();
}

bool WizzrobeVisibleWalk::isChangeable() const {
    if (*mIsCheckAnmSeqCancel_s)
        return sub_71005DD798(mActor, 2, nullptr, 0, 0);
    return mFlags.isOn(Flag::Changeable);
}

// NON_MATCHING: same logic; the original ANDs the raw flag byte with `!cancel` (no masking of the Finished bit) and computes the
// two conditions up front
bool WizzrobeVisibleWalk::isFinished() const {
    const bool cancel = *mIsCheckAnmSeqCancel_s;
    const bool finished = mFlags.isOn(Flag::Finished);
    if (cancel && finished)
        return isChangeable();
    return !cancel & finished;
}

bool WizzrobeVisibleWalk::isFailed() const {
    if (!*mIsCheckAnmSeqCancel_s)
        return mFlags.isOn(Flag::Failed);
    if (mFlags.isOn(Flag::Failed))
        return isChangeable();
    if (*mFailMoveTimer_s > 0.0f && _168.value <= sead::Mathf::epsilon())
        return isChangeable();
    return false;
}

bool WizzrobeVisibleWalk::m33() {
    if (*mAddTargetDist_s > 0.0f)
        return false;
    return LevelFlyMove::m33();
}

void WizzrobeVisibleWalk::loadParams_() {
    LevelFlyMove::loadParams_();
    getStaticParam(&mAddTargetDist_s, "AddTargetDist");
    getStaticParam(&mFailMoveTimer_s, "FailMoveTimer");
    getStaticParam(&mIsCheckAnmSeqCancel_s, "IsCheckAnmSeqCancel");
    getStaticParam(&mIsNoBrake_s, "IsNoBrake");
}

void WizzrobeVisibleWalk::calc_() {
    if (!(_168.value <= sead::Mathf::epsilon()))
        _168.update();
    if (mFlags.isOn(static_cast<Flag>(3)) && *mAddTargetDist_s > 0.0f) {
        sub_71001DA0D0();
    } else {
        LevelFlyMove::calc_();
        if (!(mFlags.isOn(static_cast<Flag>(3)) && *mAddTargetDist_s > 0.0f))
            return;
    }
    sub_71001DA1A4();
}

}  // namespace uking::action
