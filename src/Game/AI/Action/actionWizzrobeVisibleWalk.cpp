#include "Game/AI/Action/actionWizzrobeVisibleWalk.h"

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
