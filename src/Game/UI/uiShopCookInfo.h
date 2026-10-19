#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
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
    u8 _1a0[0x2e0 - 0x1a0];
    ShopCookEffectEntry entries[11];
    u8 _3e8[0x7c0 - 0x3e8];
    ShopModifierEntry modifier_entries[31];
};
static_assert(offsetof(ShopCookInfo, effects) == 0x180);
static_assert(offsetof(ShopCookInfo, modifiers) == 0x190);
static_assert(offsetof(ShopCookInfo, entries) == 0x2e0);
static_assert(offsetof(ShopCookInfo, modifier_entries) == 0x7c0);

KSYS_VISIBILITY_HIDDEN extern ShopCookInfo sUnk_71025F6960;

}  // namespace uking::ui
