#include "Game/AI/Action/actionForkNoWeaponAttackDirectParam.h"

namespace uking::action {

ForkNoWeaponAttackDirectParam::ForkNoWeaponAttackDirectParam(const InitArg& arg)
    : ForkNoWeaponAttack(arg) {}

ForkNoWeaponAttackDirectParam::~ForkNoWeaponAttackDirectParam() = default;

bool ForkNoWeaponAttackDirectParam::init_(sead::Heap* heap) {
    return ForkNoWeaponAttack::init_(heap);
}

void ForkNoWeaponAttackDirectParam::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttack::enter_(params);
}

void ForkNoWeaponAttackDirectParam::leave_() {
    ForkNoWeaponAttack::leave_();
}

void ForkNoWeaponAttackDirectParam::loadParams_() {
    ForkNoWeaponAttack::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mGuardBreakPower_s, "GuardBreakPower");
    getStaticParam(&mImpulse_s, "Impulse");
}

void ForkNoWeaponAttackDirectParam::calc_() {
    ForkNoWeaponAttack::calc_();
}

int ForkNoWeaponAttackDirectParam::m32() {
    if (*mImpulse_s >= 0)
        return *mImpulse_s;
    return ForkNoWeaponAttackBase::m32();
}

int ForkNoWeaponAttackDirectParam::m33() {
    if (*mAttackPower_s >= 0)
        return *mAttackPower_s * *mAttackPowerScale_s;
    return ForkNoWeaponAttackBase::m33();
}

int ForkNoWeaponAttackDirectParam::m34() {
    if (*mGuardBreakPower_s >= 0)
        return *mGuardBreakPower_s;
    return ForkNoWeaponAttackBase::m34();
}

}  // namespace uking::action
