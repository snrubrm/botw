#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

// Shared EquipDisplay helpers; source placement and the second helper's reference argument are inferred
// from their native callers and neighboring functions.
bool sub_7100701774(ksys::act::Actor* weapon, s32 slot);
bool sub_710070181C(ksys::act::Actor* actor, const sead::SafeString& bone_name);
