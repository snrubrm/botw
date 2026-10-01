#include "Game/AI/Action/actionNeckSpin.h"

namespace uking::action {

NeckSpin::NeckSpin(const InitArg& arg) : StopASPlay(arg) {}

NeckSpin::~NeckSpin() = default;

bool NeckSpin::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void NeckSpin::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
}

void NeckSpin::leave_() {
    StopASPlay::leave_();
}

void NeckSpin::loadParams_() {
    StopASPlay::loadParams_();
    getStaticParam(&mSpinSpeed_s, "SpinSpeed");
    getStaticParam(&mNeckUDAngle_s, "NeckUDAngle");
}

void NeckSpin::calc_() {
    _58.updateStats();
    m33();
    StopASPlay::calc_();
}

float NeckSpin::m32() {
    return _58.mean;
}

}  // namespace uking::action
