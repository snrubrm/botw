#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"

namespace uking::action {

ForkAttackWithWeaponOrWithout::ForkAttackWithWeaponOrWithout(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAttackWithWeaponOrWithout::~ForkAttackWithWeaponOrWithout() = default;

void ForkAttackWithWeaponOrWithout::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

u32 ForkAttackWithWeaponOrWithout::sub_7100146FA0() const {
    u32 flags;
    switch (*mAttackIntensity_s) {
    case 1:
        flags = 1;
        break;
    case 2:
        flags = 2;
        break;
    case 3:
        flags = 4;
        break;
    default:
        flags = 0;
        break;
    }
    if (*mIsGuardPierce_s)
        flags |= 0x8;
    if (*mIsIniviciblePierce_s)
        flags |= 0x40;
    if (*mIsForceGuardBreak_s)
        flags |= 0x100;
    if (*mIsHeavy_s)
        flags |= 0x8000;
    if (*mIsHeavy_s)
        flags |= 0x1000;
    return flags;
}

void ForkAttackWithWeaponOrWithout::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mIsHammer_s, "IsHammer");
}

}  // namespace uking::action
