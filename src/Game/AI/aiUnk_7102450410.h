#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act { class Actor; }

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
        // Declaration only; original source name and void return are inferred.
        void sub_7100708B64();
        // 0x71007086ac (ForkOnLeaveGolemChemReset::leave_, ForkASTrgGolemChemicalReset::calc_); declaration only.
        void sub_71007086AC();
        // Declaration only: per-part chemical controller update called by GolemRootBase.
        void sub_71007083DC();

        void sub_7100708A44(const sead::SafeString& name);

        // Actor and animation coordinates used by the part-animation dispatcher.
        ksys::act::Actor* mActor;
        u8 _8[0x28 - 0x8];
        s32 mASSlot;
        s32 mASBank;
        u8 _30[0xa8 - 0x30];
        s32 _a8;
        u8 _ac[4];
        s32 _b0;  // GolemChemicalResetSelect::enter_ tests entry 0 for 4
        sead::BitFlag8 _b4;  // bit 0 tested by sub_71007090F4
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
