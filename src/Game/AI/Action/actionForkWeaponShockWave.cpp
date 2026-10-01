#include "Game/AI/Action/actionForkWeaponShockWave.h"

namespace uking::action {

ForkWeaponShockWave::ForkWeaponShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkWeaponShockWave::~ForkWeaponShockWave() = default;

void ForkWeaponShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _48 = false;
}

void ForkWeaponShockWave::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mShockWaveRadius_s, "ShockWaveRadius");
    getStaticParam(&mUnderRayLength_s, "UnderRayLength");
}

void ForkWeaponShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
