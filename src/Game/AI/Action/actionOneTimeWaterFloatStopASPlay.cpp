#include "Game/AI/Action/actionOneTimeWaterFloatStopASPlay.h"

namespace uking::action {

OneTimeWaterFloatStopASPlay::OneTimeWaterFloatStopASPlay(const InitArg& arg)
    : WaterFloatImmobile(arg) {}

bool OneTimeWaterFloatStopASPlay::init_(sead::Heap* heap) {
    return WaterFloatImmobile::init_(heap);
}

void OneTimeWaterFloatStopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
    playAS(mASName_s.cstr(), *mIgnoreSameAS_s, 0, 0, -1.0f);
    mFlags.reset(Flag::Changeable);
}

void OneTimeWaterFloatStopASPlay::leave_() {
    WaterFloatImmobile::leave_();
}

void OneTimeWaterFloatStopASPlay::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getStaticParam(&mIgnoreSameAS_s, "IgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void OneTimeWaterFloatStopASPlay::calc_() {
    WaterFloatImmobile::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
