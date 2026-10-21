#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <devenv/seadEnvUtil.h>
#include <prim/seadSafeString.h>
#include "Game/Cooking/cookManager.h"
#include "KingSystem/Utils/Types.h"

namespace uking::ui {

// The global info block at 0x71025f6960 (filled by the static initializer 0x7100a9fd94). Its effect and
// modifier buffers are at +0x180 / +0x190, with inline records at +0x2e0 / +0x7c0. Unmodelled fields
// retain their storage. The MovingSpeed name is "AllSpeed".
struct ShopCookEffectEntry {
    CookEffectId effect;
    sead::SafeString name;
};
static_assert(sizeof(ShopCookEffectEntry) == 0x18);

// The initializer fills 31 modifier records, each 0x20 bytes. The two final integers are
// producer-backed metadata; the message lookup reads only id and name.
struct ShopModifierEntry {
    s32 id;
    sead::SafeString name;
    s32 _18;
    s32 _1c;
};
static_assert(sizeof(ShopModifierEntry) == 0x20);

struct ShopCookInfo {
    u8 _0[0x180];
    sead::Buffer<ShopCookEffectEntry> effects;
    sead::Buffer<ShopModifierEntry> modifiers;
    u8 _1a0[0x1c0 - 0x1a0];
    // 0x71025f6b20: the separator between hours, minutes and seconds.
    /* 0x1c0 */ sead::SafeString timeSeparator = ":";
    // 0x71025f6b30 / 0x71025f6b60: the hero soul and seal actor names (14 entries at +0x200).
    /* 0x1d0 */ sead::Buffer<sead::SafeString> heroSoulNames{14, heroSoulNameStrings};
    // 0x71025f6b40: the region languages whose decimal separator is "." (others use ",").
    /* 0x1e0 */ sead::RegionLanguageID decimalPointLanguages[8]{
        sead::RegionLanguageID::JPja, sead::RegionLanguageID::USen,
        sead::RegionLanguageID::USes, sead::RegionLanguageID::EUen,
        sead::RegionLanguageID::EUnl, sead::RegionLanguageID::KRko,
        sead::RegionLanguageID::CNzh, sead::RegionLanguageID::TWzh,
    };
    /* 0x200 */ sead::SafeString heroSoulNameStrings[14]{
        "Obj_HeroSoul_Rito",     "Obj_HeroSoul_Goron",     "Obj_HeroSoul_Gerudo",
        "Obj_HeroSoul_Zora",     "Obj_DungeonClearSeal",   "Obj_WarpDLC",
        "Obj_DLC_HeroSeal_Rito", "Obj_DLC_HeroSeal_Goron", "Obj_DLC_HeroSeal_Gerudo",
        "Obj_DLC_HeroSeal_Zora", "Obj_DLC_HeroSoul_Rito",  "Obj_DLC_HeroSoul_Goron",
        "Obj_DLC_HeroSoul_Gerudo", "Obj_DLC_HeroSoul_Zora",
    };
    ShopCookEffectEntry entries[11];
    u8 _3e8[0x7c0 - 0x3e8];
    ShopModifierEntry modifier_entries[31];
};
static_assert(offsetof(ShopCookInfo, effects) == 0x180);
static_assert(offsetof(ShopCookInfo, modifiers) == 0x190);
static_assert(offsetof(ShopCookInfo, timeSeparator) == 0x1c0);
static_assert(offsetof(ShopCookInfo, heroSoulNames) == 0x1d0);
static_assert(offsetof(ShopCookInfo, decimalPointLanguages) == 0x1e0);
static_assert(offsetof(ShopCookInfo, heroSoulNameStrings) == 0x200);
static_assert(offsetof(ShopCookInfo, entries) == 0x2e0);
static_assert(offsetof(ShopCookInfo, modifier_entries) == 0x7c0);

KSYS_VISIBILITY_HIDDEN extern ShopCookInfo sUnk_71025F6960;

}  // namespace uking::ui
