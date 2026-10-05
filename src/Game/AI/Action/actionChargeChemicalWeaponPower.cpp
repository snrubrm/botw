#include "Game/AI/Action/actionChargeChemicalWeaponPower.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ChargeChemicalWeaponPower::ChargeChemicalWeaponPower(const InitArg& arg)
    : SetChemicalWeaponPower(arg) {}

ChargeChemicalWeaponPower::~ChargeChemicalWeaponPower() = default;

bool ChargeChemicalWeaponPower::init_(sead::Heap* heap) {
    return SetChemicalWeaponPower::init_(heap);
}

void ChargeChemicalWeaponPower::enter_(ksys::act::ai::InlineParamPack* params) {
    SetChemicalWeaponPower::enter_(params);
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        if (weapon->_d38)
            weapon->_d38->_18 &= ~0x10;
    }
}

void ChargeChemicalWeaponPower::leave_() {
    SetChemicalWeaponPower::leave_();
}

void ChargeChemicalWeaponPower::loadParams_() {
    SetChemicalWeaponPower::loadParams_();
}

void ChargeChemicalWeaponPower::calc_() {
    SetChemicalWeaponPower::calc_();
}

}  // namespace uking::action
