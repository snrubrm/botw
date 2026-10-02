#include "Game/AI/Action/actionNeckSpin.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

NeckSpin::NeckSpin(const InitArg& arg) : StopASPlay(arg) {}

bool NeckSpin::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void NeckSpin::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
}

void NeckSpin::leave_() {
    sub_71005DB498(mActor);
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

void NeckSpin::m33() {
    _64 += m32();
    _64 = ksys::util::sub_71011EF0CC(_64);
    sub_71005DB44C(mActor, _64, *mNeckUDAngle_s);
}

}  // namespace uking::action
