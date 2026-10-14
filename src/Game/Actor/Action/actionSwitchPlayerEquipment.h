#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

// 0x710028da58: switches the equipment slot named `name` (the name is a guess). In the original the
// first argument register (x0) is not set by the callers and `name` is in x1: the function has an
// unused leading parameter (an empty class passed by value; unknown type), which is not modelled.
bool sub_710028DA58(const sead::SafeString& name);
// 0x710028dbc8 (CSV: PauseMenuDataMgr::switchPlayerArmor): switches the armor piece `name` (same
// unused leading parameter as sub_710028DA58).
bool sub_710028DBC8(const sead::SafeString& name, bool needs_head_b);

class SwitchPlayerEquipment : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchPlayerEquipment, ksys::act::ai::Action)
public:
    explicit SwitchPlayerEquipment(const InitArg& arg);
    ~SwitchPlayerEquipment() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mUnequipWeapon_d{};
    // dynamic_param at offset 0x28
    bool* mUnequipShield_d{};
    // dynamic_param at offset 0x30
    bool* mUnequipBow_d{};
    // dynamic_param at offset 0x38
    bool* mUnequipArmorHead_d{};
    // dynamic_param at offset 0x40
    bool* mUnequipArmorUpper_d{};
    // dynamic_param at offset 0x48
    bool* mUnequipArmorLower_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mPorchItemName_Weapon_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mPorchItemName_Shield_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mPorchItemName_Bow_d{};
    // dynamic_param at offset 0x80
    sead::SafeString mPorchItemName_ArmorHead_d{};
    // dynamic_param at offset 0x90
    sead::SafeString mPorchItemName_ArmorUpper_d{};
    // dynamic_param at offset 0xa0
    sead::SafeString mPorchItemName_ArmorLower_d{};
    // dynamic_param at offset 0xb0
    sead::SafeString mPorchItemName_Arrow_d{};
    bool _c0 = false;
    bool _c1 = false;
};

}  // namespace uking::action
