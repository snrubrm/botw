#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
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

        u8 _0[0xb8];
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0xb8);

    Unk_7102450410();
    ~Unk_7102450410() override;

    sead::Buffer<Entry> _8;
    u16 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450410, 0x20);
