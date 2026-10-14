#include "Game/Actor/Action/actionLastBossBlowOff.h"

namespace uking::action {

LastBossBlowOff::LastBossBlowOff(const InitArg& arg) : BlownOff(arg) {}

LastBossBlowOff::~LastBossBlowOff() = default;

bool LastBossBlowOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void LastBossBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    _160 = ksys::Timer(*mTime_s, *mTime_s);
}

void LastBossBlowOff::leave_() {
    BlownOff::leave_();
}

void LastBossBlowOff::loadParams_() {
    BlownOff::loadParams_();
}

void LastBossBlowOff::calc_() {
    BlownOff::calc_();
    _160.update();
}

bool LastBossBlowOff::m36() {
    return Ragdoll::m36();
}

s32 LastBossBlowOff::m40() {
    return _160.value;
}

}  // namespace uking::action
