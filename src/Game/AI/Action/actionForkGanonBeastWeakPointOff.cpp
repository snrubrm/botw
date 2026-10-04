#include "Game/AI/Action/actionForkGanonBeastWeakPointOff.h"

// Declaration only; original global name retained, source namespace unknown.
void ganonBeastWeakPointSetOff(ksys::act::Actor* actor, s32 point, s32 target_slot,
                              bool reset, bool emit);

namespace uking::action {

ForkGanonBeastWeakPointOff::ForkGanonBeastWeakPointOff(const InitArg& arg)
    : ForkGanonBeastWeakPoint(arg) {}

ForkGanonBeastWeakPointOff::~ForkGanonBeastWeakPointOff() = default;

bool ForkGanonBeastWeakPointOff::init_(sead::Heap* heap) {
    return ForkGanonBeastWeakPoint::init_(heap);
}

void ForkGanonBeastWeakPointOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkGanonBeastWeakPoint::enter_(params);
}

void ForkGanonBeastWeakPointOff::leave_() {
    ForkGanonBeastWeakPoint::leave_();
}

void ForkGanonBeastWeakPointOff::loadParams_() {
    ForkGanonBeastWeakPoint::loadParams_();
}

void ForkGanonBeastWeakPointOff::calc_() {
    ForkGanonBeastWeakPoint::calc_();
}

void ForkGanonBeastWeakPointOff::m32(s32 point, s32 target_slot) {
    ganonBeastWeakPointSetOff(mActor, point, target_slot, false, true);
}

}  // namespace uking::action
