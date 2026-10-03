#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// Golem chemical controller (vtable 0x7102450410, RTTI typeInfo static 0x71025b29f8): embedded in
// GolemRootBase (_2f0) and shared with the golem AIs through the GolemChemicalController AI tree
// variable. Its functions live in the listener TU (0x71007080e0-0x7100708fec,
// aiUnk_7102357210.cpp). Placeholder name = vtable address.
class Unk_7102450410 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450410, Unk_71025afb58)
public:
    // 0xb8-byte entries (one per controlled part).
    struct Entry {
        ~Entry();

        u8 _0[0xb0];
        s32 _b0;  // GolemChemicalResetSelect::enter_ (== 4 -> "ケミカル復帰")
        bool _b4;
        bool _b5;
        u8 _b6[2];
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0xb8);

    Unk_7102450410();
    ~Unk_7102450410() override;

    sead::Buffer<Entry> _8;
    sead::BitFlag16 _18;  // bit 0: set by MiniGolemLifted::enter_, cleared by leave_
};
KSYS_CHECK_SIZE_NX150(Unk_7102450410, 0x20);

// 0x71007090f4: whether any entry of the controller (may be null) has _b4 set.
bool sub_71007090F4(const Unk_7102450410* controller);
