#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>

namespace ksys::act {

// Armor strings (placeholder names = address; the real names are unknown). Defined in Game/Actor/actArmorBase.cpp in
// address order; initialised by the static initializer 0x7100e2d0f0 (CSV: sinitArmorStrings).
extern sead::SafeString sUnk_71026022e8;  // "Armor_Default"
extern sead::SafeArray<sead::SafeString, 6> sUnk_71026022f8;
extern sead::SafeArray<sead::SafeString, 23> sUnk_7102602358;
extern sead::SafeArray<sead::SafeString, 24> sUnk_71026024c8;

}  // namespace ksys::act

namespace uking::act {

// Initialised by the same static initializer (0x7100e2d0f0).
extern sead::SafeString ArmorDyeColor;                // "ArmorDyeColor"
extern sead::SafeString EnableDynamicColorChange;     // "EnableDynamicColorChange"

}  // namespace uking::act
