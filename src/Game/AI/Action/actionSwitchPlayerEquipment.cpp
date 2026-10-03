#include "Game/AI/Action/actionSwitchPlayerEquipment.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SwitchPlayerEquipment::SwitchPlayerEquipment(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchPlayerEquipment::~SwitchPlayerEquipment() = default;

bool SwitchPlayerEquipment::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the callees sub_710028DA58 / sub_710028DBC8 take an unused empty-class first
// parameter (callers leave x0 alone, name in x1); otherwise only the placement of the vtable load of the
// "action::SwitchPlayerEquipment" temporary and an explicit `eor` differ.
void SwitchPlayerEquipment::enter_(ksys::act::ai::InlineParamPack* params) {
    _c0 = true;
    _c1 = false;

    u32 flags = 0;

    bool changed_Sword = false;
    if (!mPorchItemName_Weapon_d.isEmpty() && !*mUnequipWeapon_d) {
        changed_Sword = sub_710028DA58(mPorchItemName_Weapon_d);
    } else if (*mUnequipWeapon_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (mgr) {
            auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
            if (player) {
                mgr->unequipAll(ui::PouchItemType::Sword);
                player->switchEquipment(mgr->getDefaultEquipment(ui::EquipmentSlot::WeaponRight),
                                        0x1e, -1);
                changed_Sword = true;
            }
        }
    }
    if (changed_Sword)
        flags |= 2;

    bool changed_Shield = false;
    if (!mPorchItemName_Shield_d.isEmpty() && !*mUnequipShield_d) {
        changed_Shield = sub_710028DA58(mPorchItemName_Shield_d);
    } else if (*mUnequipShield_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (mgr) {
            auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
            if (player) {
                mgr->unequipAll(ui::PouchItemType::Shield);
                player->switchEquipment(mgr->getDefaultEquipment(ui::EquipmentSlot::WeaponLeft),
                                        0x1e, -1);
                changed_Shield = true;
            }
        }
    }
    if (changed_Shield)
        flags |= 4;

    bool changed_Bow = false;
    if (!mPorchItemName_Bow_d.isEmpty() && !*mUnequipBow_d) {
        changed_Bow = sub_710028DA58(mPorchItemName_Bow_d);
    } else if (*mUnequipBow_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (mgr) {
            auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
            if (player) {
                mgr->unequipAll(ui::PouchItemType::Bow);
                player->switchEquipment(mgr->getDefaultEquipment(ui::EquipmentSlot::WeaponBow),
                                        0x1e, -1);
                changed_Bow = true;
            }
        }
    }
    if (changed_Bow)
        flags |= 8;

    bool changed_head = false;
    if (!mPorchItemName_ArmorHead_d.isEmpty() && !*mUnequipArmorHead_d) {
        bool needs_head_b;
        if (mPorchItemName_ArmorUpper_d.isEmpty()) {
            needs_head_b = false;
            if (auto* mgr = ui::PauseMenuDataMgr::instance()) {
                if (auto* name = mgr->getEquippedItemName(ui::PouchItemType::ArmorHead)) {
                    if (!name->isEmpty())
                        needs_head_b = act::needsArmorHeadB(mPorchItemName_ArmorHead_d, *name);
                }
            }
        } else {
            needs_head_b =
                act::needsArmorHeadB(mPorchItemName_ArmorHead_d, mPorchItemName_ArmorUpper_d);
        }
        changed_head = sub_710028DBC8(mPorchItemName_ArmorHead_d, needs_head_b);
    } else if (*mUnequipArmorHead_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
        if (mgr && create_mgr) {
            mgr->unequipAll(ui::PouchItemType::ArmorHead);
            create_mgr->requestCreateDefaultArmor(3, "action::SwitchPlayerEquipment");
            changed_head = true;
        }
    } else if (!mPorchItemName_ArmorUpper_d.isEmpty() || *mUnequipArmorUpper_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (mgr) {
            auto* item = mgr->getEquippedItem(ui::PouchItemType::ArmorHead);
            if (item && item->isInInventory() && act::isArmorHeadMantleType2(item->getName())) {
                auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
                if (create_mgr) {
                    if (mPorchItemName_ArmorUpper_d.isEmpty()) {
                        create_mgr->requestCreateArmor(item->getName(), item->getValue(),
                                                       "action::SwitchPlayerEquipment");
                    } else if (act::isArmorUpperNotUseMantleType0(mPorchItemName_ArmorUpper_d)) {
                        create_mgr->requestCreateArmorHeadB(item->getName(), item->getValue(),
                                                            "action::SwitchPlayerEquipment");
                    } else {
                        create_mgr->requestCreateArmor(item->getName(), item->getValue(),
                                                       "action::SwitchPlayerEquipment");
                    }
                }
            }
        }
    }
    if (changed_head)
        flags |= 0x10;

    bool changed_upper = false;
    if (!mPorchItemName_ArmorUpper_d.isEmpty() && !*mUnequipArmorUpper_d) {
        changed_upper = sub_710028DBC8(mPorchItemName_ArmorUpper_d, false);
    } else if (*mUnequipArmorUpper_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
        if (mgr && create_mgr) {
            mgr->unequipAll(ui::PouchItemType::ArmorUpper);
            create_mgr->requestCreateDefaultArmor(4, "action::SwitchPlayerEquipment");
            changed_upper = true;
        }
    }
    if (changed_upper)
        flags = 1;

    bool check;
    if (!mPorchItemName_ArmorLower_d.isEmpty() && !*mUnequipArmorLower_d) {
        const bool switched = sub_710028DBC8(mPorchItemName_ArmorLower_d, false);
        check = !(flags == 0 && !switched);
    } else if (*mUnequipArmorLower_d) {
        auto* mgr = ui::PauseMenuDataMgr::instance();
        auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
        if (mgr && create_mgr) {
            mgr->unequipAll(ui::PouchItemType::ArmorLower);
            create_mgr->requestCreateDefaultArmor(5, "action::SwitchPlayerEquipment");
            check = true;
        } else {
            check = flags != 0;
        }
    } else {
        check = flags != 0;
    }

    if (check) {
        auto* player_info = ksys::act::PlayerInfo::instance();
        if (!player_info || !player_info->getPlayer()) {
            setFailed();
            return;
        }
    }

    if (!mPorchItemName_Arrow_d.isEmpty()) {
        if (auto* mgr = ui::PauseMenuDataMgr::instance())
            mgr->switchEquipment(mPorchItemName_Arrow_d);
    }
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
