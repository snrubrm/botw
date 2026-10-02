#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// Unnamed class of the object shared through the "RemainsWaterBattleInfo" AI tree variable: embedded
// in RemainsWaterRoot (+0x58), which points the variable at it (RemainsWaterRoot::sub_710054BAC8)
// and clears it again in leave_. Placeholder name = vtable address (RTTI typeInfo 0x71025b5618).
// All its functions (D2 0x710054b904, D0, RTTI) are inline and emitted in the RemainsWaterRoot TU.
class Unk_7102419cb0 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102419cb0, Unk_71025afb58)
public:
    ~Unk_7102419cb0() override {
        for (auto*& ptr : _8)
            ptr = nullptr;
    }

    // RemainsWaterBulletShooter::enter_ counts the non-null entries; RemainsWaterBulletController
    // clears them in its destructor.
    void* _8[5]{};
    u32 _30 = 0;
    bool _34 = false;  // RemainsWaterBattleRoot::handleMessage_ (message 0x8000069)
    s32 _38 = 0;  // number of destroyed weak points (RemainsWaterRoot::sub_710054BAC8)
    s32 _3c = 0;  // phase (RemainsWaterBattleRoot::sub_7100545B8C switches on 0/1/2)
};
KSYS_CHECK_SIZE_NX150(Unk_7102419cb0, 0x40);
