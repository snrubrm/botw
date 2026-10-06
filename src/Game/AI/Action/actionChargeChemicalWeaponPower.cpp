#include "Game/AI/Action/actionChargeChemicalWeaponPower.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        auto* as_list = weapon->getASList();
        if (!as_list) {
            setFailed();
            return;
        }
        as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
        if (!weapon->_d38) {
            setFailed();
            return;
        }
        const s32 max_charge = s32(weapon->_d38->sub_71002EF74C());
        if (max_charge <= 0) {
            setFailed();
            return;
        }
        const f32 ratio = (weapon->_d38 ? weapon->_d38->_14 : 0.0f) / f32(max_charge);
        const bool flag = weapon->m214();
        sub_7100069E08(ratio);
        sub_7100069F90(flag, ratio);
        sub_7100069FD0(weapon->_d38 ? weapon->_d38->_18 >> 3 & 1 : false);
    }
}

}  // namespace uking::action
