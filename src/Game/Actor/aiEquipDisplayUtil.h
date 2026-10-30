#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}
namespace uking::act {
struct WeaponModifierInfo;
}

// Shared EquipDisplay helpers; source placement and the bone helper's reference argument are inferred
// from their native callers and neighboring functions.
// The EquipStandSlot consumers use categories 0-2 and 3 for an invalid slot; scope inferred.
s32 sub_7100700A4C(s32 slot);
bool sub_7100700A78(s32 slot);
// Argument reference and const qualification are inferred from the weapon caller and flag setters.
bool sub_7100700D5C(const sead::SafeString& name, s32 life,
                    const uking::act::WeaponModifierInfo* modifier, s32 slot);
// Actor pointer and return type inferred from the native caller and weapon RTTI guard.
bool sub_7100700E5C(ksys::act::Actor* actor, s32 slot);
bool sub_7100700F1C(s32 slot);
bool sub_7100701774(ksys::act::Actor* weapon, s32 slot);
bool sub_710070181C(ksys::act::Actor* actor, const sead::SafeString& bone_name);
