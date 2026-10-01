#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"
#include <prim/seadStringBuilder.h>

namespace uking::action {

ForkNoWeaponAttackBase::ForkNoWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkNoWeaponAttackBase::~ForkNoWeaponAttackBase() = default;

bool ForkNoWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkNoWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
    mFlags.set(Flag::Changeable);
}

void ForkNoWeaponAttackBase::leave_() {
    ForkAttackWithWeaponOrWithout::leave_();
}

// NON_MATCHING: regalloc (&mAttackType_s kept in x20 from before the first call)
void ForkNoWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mAttackPowerScale_s, "AttackPowerScale");
    getStaticParam(&mIsUseAttackParam_s, "IsUseAttackParam");
    sead::FixedStringBuilder<64> name;
    for (int i = 0; i < 3; ++i) {
        name.format("AtkBodyName%d", i + 1);
        getStaticParam(&mAtkBodyName_s[i], name.cstr());
    }
    getStaticParam(&mChmName1_s, "ChmName1");
}

void ForkNoWeaponAttackBase::calc_() {
    ForkAttackWithWeaponOrWithout::calc_();
}

int ForkNoWeaponAttackBase::m35() {
    return 1;
}

}  // namespace uking::action
