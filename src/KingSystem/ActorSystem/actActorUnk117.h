#pragma once

#include <basis/seadTypes.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Argument of Actor vtable slot 117 (and of Actor::x_17, which forwards it to the actor's
// weapons / parts / connected calc child and parent). Built by Actor::doHandleMessage_,
// Actor::x_15 and two more wrappers: _0 is the kind (0, 2 or 3), _4 the current core number (the
// callee clamps it to < 3 and uses it as an index) and the other fields depend on the kind.
struct Unk117 {
    // Kind 3 payload (placeholder names; HorseBase::m117 compares the two strings of each entry with
    // "HyruleCastle" / "GanonDead"): four entries of 0x10 bytes starting at +0x10, the second word of
    // each is a pointer to an Entry (may be null).
    struct Entry {
        u8 _0[0x10];
        sead::FixedSafeString<64> _10;
        sead::FixedSafeString<64> _68;
    };
    struct Kind3 {
        struct Item {
            void* _0;
            Entry* mEntry;
        };
        u8 _0[0x10];
        Item mItems[4];
    };

    u32 _0 = 0;
    sead::CoreId _4;
    Kind3* _8;   // kind 3
    void* _10;  // kind 0
    const char* _18;  // kind 0
};
KSYS_CHECK_SIZE_NX150(Unk117, 0x20);

}  // namespace ksys::act
