#include "Game/AI/Action/actionSiteBossBlowOff.h"

namespace uking::action {

SiteBossBlowOff::SiteBossBlowOff(const InitArg& arg) : BlownOff(arg) {}

SiteBossBlowOff::~SiteBossBlowOff() = default;

bool SiteBossBlowOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void SiteBossBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    _160 = ksys::Timer(*mTime_s, *mTime_s);
}

void SiteBossBlowOff::leave_() {
    BlownOff::leave_();
}

void SiteBossBlowOff::loadParams_() {
    BlownOff::loadParams_();
}

void SiteBossBlowOff::calc_() {
    BlownOff::calc_();
    _160.update();
}

bool SiteBossBlowOff::m36() {
    return Ragdoll::m36();
}

s32 SiteBossBlowOff::m40() {
    return _160.value;
}

}  // namespace uking::action
