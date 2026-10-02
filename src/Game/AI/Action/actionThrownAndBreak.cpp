#include "Game/AI/Action/actionThrownAndBreak.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ThrownAndBreak::ThrownAndBreak(const InitArg& arg) : Thrown(arg) {}

ThrownAndBreak::~ThrownAndBreak() = default;

bool ThrownAndBreak::init_(sead::Heap* heap) {
    return Thrown::init_(heap);
}

void ThrownAndBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    Thrown::enter_(params);
}

void ThrownAndBreak::leave_() {
    Thrown::leave_();
    callDeleteAndCreateDropAndEmit(mActor, 0);
}

void ThrownAndBreak::loadParams_() {
    Thrown::loadParams_();
}

void ThrownAndBreak::calc_() {
    Thrown::calc_();
}

}  // namespace uking::action
