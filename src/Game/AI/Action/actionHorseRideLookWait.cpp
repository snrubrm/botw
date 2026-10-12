#include "Game/AI/Action/actionHorseRideLookWait.h"

namespace uking::action {

HorseRideLookWait::HorseRideLookWait(const InitArg& arg) : HorseRideBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideLookWait::~HorseRideLookWait() {
    ;
}

bool HorseRideLookWait::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideLookWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    if (!mASName_s.isEmpty())
        sub_71001AD8A0(mASName_s.cstr(), true);
    mFlags.set(Flag::Changeable);
}

void HorseRideLookWait::leave_() {
    sub_71001ADAA8();
    HorseRideBase::leave_();
}

void HorseRideLookWait::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideLookWait::calc_() {
    HorseRideBase::calc_();
    sub_71001ADAA0(*mTargetPos_d);
}

}  // namespace uking::action
