#include "Game/AI/Action/actionForkWeaponShockWaveCheckValue.h"

namespace uking::action {

ForkWeaponShockWaveCheckValue::ForkWeaponShockWaveCheckValue(const InitArg& arg)
    : ForkWeaponShockWave(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkWeaponShockWaveCheckValue::~ForkWeaponShockWaveCheckValue() {
    ;
}

bool ForkWeaponShockWaveCheckValue::init_(sead::Heap* heap) {
    return ForkWeaponShockWave::init_(heap);
}

void ForkWeaponShockWaveCheckValue::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponShockWave::enter_(params);
}

void ForkWeaponShockWaveCheckValue::leave_() {
    ForkWeaponShockWave::leave_();
}

void ForkWeaponShockWaveCheckValue::loadParams_() {
    ForkWeaponShockWave::loadParams_();
    getStaticParam(&mAtEventValue_s, "AtEventValue");
}

void ForkWeaponShockWaveCheckValue::calc_() {
    ForkWeaponShockWave::calc_();
}

}  // namespace uking::action
