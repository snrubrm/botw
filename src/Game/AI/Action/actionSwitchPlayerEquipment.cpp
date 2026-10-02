#include "Game/AI/Action/actionSwitchPlayerEquipment.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SwitchPlayerEquipment::SwitchPlayerEquipment(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchPlayerEquipment::~SwitchPlayerEquipment() = default;

bool SwitchPlayerEquipment::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchPlayerEquipment::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchPlayerEquipment::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchPlayerEquipment::loadParams_() {
    getDynamicParam(&mUnequipWeapon_d, "UnequipWeapon");
    getDynamicParam(&mUnequipShield_d, "UnequipShield");
    getDynamicParam(&mUnequipBow_d, "UnequipBow");
    getDynamicParam(&mUnequipArmorHead_d, "UnequipArmorHead");
    getDynamicParam(&mUnequipArmorUpper_d, "UnequipArmorUpper");
    getDynamicParam(&mUnequipArmorLower_d, "UnequipArmorLower");
    getDynamicParam(&mPorchItemName_Weapon_d, "PorchItemName_Weapon");
    getDynamicParam(&mPorchItemName_Shield_d, "PorchItemName_Shield");
    getDynamicParam(&mPorchItemName_Bow_d, "PorchItemName_Bow");
    getDynamicParam(&mPorchItemName_ArmorHead_d, "PorchItemName_ArmorHead");
    getDynamicParam(&mPorchItemName_ArmorUpper_d, "PorchItemName_ArmorUpper");
    getDynamicParam(&mPorchItemName_ArmorLower_d, "PorchItemName_ArmorLower");
    getDynamicParam(&mPorchItemName_Arrow_d, "PorchItemName_Arrow");
}

void SwitchPlayerEquipment::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_c0) {
        _c0 = false;
        return;
    }
    if (!act::CreatePlayerEquipActorMgr::instance()->areAllWeaponActorsReady())
        return;
    if (!_c1) {
        if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer())
            player->setC98Locked(0x20);
        _c1 = true;
    }
    setFinished();
}

}  // namespace uking::action
