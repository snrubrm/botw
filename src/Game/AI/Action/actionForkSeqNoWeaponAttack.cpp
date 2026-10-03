#include <prim/seadFormatPrint.h>
#include "Game/AI/Action/actionForkSeqNoWeaponAttack.h"

namespace uking::action {

ForkSeqNoWeaponAttack::ForkSeqNoWeaponAttack(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkSeqNoWeaponAttack::~ForkSeqNoWeaponAttack() = default;

bool ForkSeqNoWeaponAttack::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkSeqNoWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
}

void ForkSeqNoWeaponAttack::leave_() {
    _80.sub_7100720FD0();
}

void ForkSeqNoWeaponAttack::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 2; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "ExcludeAtkName%d", i) << sead::flush;
        getStaticParam(&mExcludeAtkName_s[i], key);
    }
}

void ForkSeqNoWeaponAttack::calc_() {
    _80.sub_7100720B28();
}

}  // namespace uking::action
