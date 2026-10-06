#include "Game/AI/Action/actionStopChargeChemicalWeaponPower.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

StopChargeChemicalWeaponPower::StopChargeChemicalWeaponPower(const InitArg& arg)
    : SetChemicalWeaponPower(arg) {}

StopChargeChemicalWeaponPower::~StopChargeChemicalWeaponPower() = default;

bool StopChargeChemicalWeaponPower::init_(sead::Heap* heap) {
    return SetChemicalWeaponPower::init_(heap);
}

void StopChargeChemicalWeaponPower::loadParams_() {
    SetChemicalWeaponPower::loadParams_();
}

bool StopChargeChemicalWeaponPower::oneShot_() {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        auto* as_list = weapon->getASList();
        if (!as_list)
            return false;
        if (weapon->_d38) {
            weapon->_d38->sub_71002EF850();
            if (weapon->_d38)
                weapon->_d38->_18 |= 0x10;
        }
        sub_7100069E08(0.0f);
        sub_7100069F90(false, 0.0f);
        as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    }
    return true;
}

}  // namespace uking::action
