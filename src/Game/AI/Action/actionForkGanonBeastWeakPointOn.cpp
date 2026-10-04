#include "Game/AI/Action/actionForkGanonBeastWeakPointOn.h"

// Declaration only; original global name retained, source namespace unknown.
void ganonBeastWeakPointSetOn(ksys::act::Actor* actor, s32 point, s32 target_slot);

namespace uking::action {

ForkGanonBeastWeakPointOn::ForkGanonBeastWeakPointOn(const InitArg& arg)
    : ForkGanonBeastWeakPoint(arg) {}

ForkGanonBeastWeakPointOn::~ForkGanonBeastWeakPointOn() = default;

bool ForkGanonBeastWeakPointOn::init_(sead::Heap* heap) {
    return ForkGanonBeastWeakPoint::init_(heap);
}

void ForkGanonBeastWeakPointOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkGanonBeastWeakPoint::enter_(params);
}

void ForkGanonBeastWeakPointOn::leave_() {
    ForkGanonBeastWeakPoint::leave_();
}

void ForkGanonBeastWeakPointOn::loadParams_() {
    ForkGanonBeastWeakPoint::loadParams_();
}

void ForkGanonBeastWeakPointOn::calc_() {
    ForkGanonBeastWeakPoint::calc_();
}

void ForkGanonBeastWeakPointOn::m32(s32 point, s32 target_slot) {
    ganonBeastWeakPointSetOn(mActor, point, target_slot);
}

}  // namespace uking::action
