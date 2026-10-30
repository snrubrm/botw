#include "Game/Actor/aiEquipDisplayUtil.h"
#include <gsys/gsysModel.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

// NON_MATCHING: the compiler combines the negative-slot return with the category selection.
s32 sub_7100700A4C(s32 slot) {
    if (slot < 0)
        return 3;
    const s32 category = slot / 100;
    return category < 3 ? category : 3;
}

// NON_MATCHING: the compiler combines the bounds checks and schedules the slot arithmetic differently.
bool sub_7100700A78(s32 slot) {
    if (slot < 0 || slot >= 300)
        return false;

    sead::FixedSafeString<64> prefix;
    switch (slot / 100) {
    case 0:
        prefix = "EquipStandSword";
        break;
    case 1:
        prefix = "EquipStandBow";
        break;
    case 2:
        prefix = "EquipStandShield";
        break;
    default:
        prefix.clear();
        break;
    }
    sead::FixedSafeString<64> flag;
    flag.format("%s_Slot", prefix.cstr());
    const s32 index = slot % 100;
    s32 size = -1;
    if (auto* manager = ksys::gdt::Manager::instance())
        manager->getParam().get().getBuffer1()->getStr64ArraySize(&size, flag);
    if (index > size)
        return false;
    const char* value = nullptr;
    ksys::gdt::getStr64ByKey(&value, flag, index, false);
    return value[0] != '\0';
}

// NON_MATCHING: the original clamps the slot category before dispatch; this switch checks it directly.
bool sub_7100700D5C(const sead::SafeString& name, s32 life,
                    const uking::act::WeaponModifierInfo* modifier, s32 slot) {
    if (slot < 0)
        return false;
    const s32 index = slot % 100;
    switch (slot / 100) {
    case 0:
        ksys::gdt::setFlag_EquipStandSword_Slot(name, index);
        ksys::gdt::setFlag_EquipStandSword_Life_Slot(life, index);
        if (modifier)
            modifier->saveEquipStandSwordFlag(index);
        break;
    case 1:
        ksys::gdt::setFlag_EquipStandBow_Slot(name, index);
        ksys::gdt::setFlag_EquipStandBow_Life_Slot(life, index);
        if (modifier)
            modifier->saveEquipStandBowFlag(index);
        break;
    case 2:
        ksys::gdt::setFlag_EquipStandShield_Slot(name, index);
        ksys::gdt::setFlag_EquipStandShield_Life_Slot(life, index);
        if (modifier)
            modifier->saveEquipStandShieldFlag(index);
        break;
    default:
        return false;
    }
    return true;
}

// NON_MATCHING: the compiler keeps the actor-name address in an extra saved register.
bool sub_7100700E5C(ksys::act::Actor* actor, s32 slot) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor);
    if (!weapon)
        return false;
    const s32* life = weapon->getLife();
    return sub_7100700D5C(weapon->getName(), life ? *life : 1, &weapon->_f98, slot);
}

// NON_MATCHING: the compiler combines the lower and upper bound checks.
bool sub_7100700F1C(s32 slot) {
    if (slot < 0 || slot >= 300)
        return false;
    const s32 index = slot % 100;
    uking::act::WeaponModifierInfo modifier;
    switch (slot / 100) {
    case 0:
        ksys::gdt::setFlag_EquipStandSword_Slot("", index);
        ksys::gdt::setFlag_EquipStandSword_Life_Slot(0, index);
        modifier.saveEquipStandSwordFlag(index);
        break;
    case 1:
        ksys::gdt::setFlag_EquipStandBow_Slot("", index);
        ksys::gdt::setFlag_EquipStandBow_Life_Slot(0, index);
        modifier.saveEquipStandBowFlag(index);
        break;
    case 2:
        ksys::gdt::setFlag_EquipStandShield_Slot("", index);
        ksys::gdt::setFlag_EquipStandShield_Life_Slot(0, index);
        modifier.saveEquipStandShieldFlag(index);
        break;
    default:
        return false;
    }
    return true;
}

bool sub_7100701774(ksys::act::Actor* weapon, s32 slot) {
    if (slot != 0)
        return true;
    auto* typed_weapon = sead::DynamicCast<uking::act::Weapon>(weapon);
    return typed_weapon && typed_weapon->isMasterSword();
}

bool sub_710070181C(ksys::act::Actor* actor, const sead::SafeString& bone_name) {
    auto* model = actor->getModel();
    return model && model->searchBone(bone_name).isValid();
}
