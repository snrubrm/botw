#include "Game/Actor/aiEquipDisplayUtil.h"
#include <gsys/gsysModel.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

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
