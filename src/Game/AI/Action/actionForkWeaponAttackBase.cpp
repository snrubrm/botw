#include "Game/AI/Action/actionForkWeaponAttackBase.h"

namespace uking::action {

ForkWeaponAttackBase::ForkWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkWeaponAttackBase::~ForkWeaponAttackBase() = default;

bool ForkWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
    mFlags.set(Flag::Changeable);
    _68 = false;
}

void ForkWeaponAttackBase::leave_() {
    m33();
}

void ForkWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mIsNoRod_s, "IsNoRod");
}

// NON_MATCHING: stack frame is 0x10 larger in the original (the string sits at sp+8)
void ForkWeaponAttackBase::calc_() {
    sead::SafeString name;
    if (m34(&name)) {
        m32(m36(), name, _68, 1.0f);
        _68 = true;
    } else if (m35()) {
        m33();
    }
}

int ForkWeaponAttackBase::m36() {
    return 0;
}

}  // namespace uking::action
