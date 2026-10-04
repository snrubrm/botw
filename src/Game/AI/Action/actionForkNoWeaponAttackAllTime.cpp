#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"

namespace uking::action {

ForkNoWeaponAttackAllTime::ForkNoWeaponAttackAllTime(const InitArg& arg)
    : ForkNoWeaponAttackBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkNoWeaponAttackAllTime::~ForkNoWeaponAttackAllTime() {
    ;
}

bool ForkNoWeaponAttackAllTime::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackBase::init_(heap);
}

void ForkNoWeaponAttackAllTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackBase::enter_(params);
}

void ForkNoWeaponAttackAllTime::leave_() {
    sub_710015E71C();
    ForkNoWeaponAttackBase::leave_();
}

void ForkNoWeaponAttackAllTime::loadParams_() {
    ForkNoWeaponAttackBase::loadParams_();
    getStaticParam(&mAtDirString_s, "AtDirString");
}

void ForkNoWeaponAttackAllTime::calc_() {
    ForkNoWeaponAttackBase::calc_();
}

}  // namespace uking::action
