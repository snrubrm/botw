#pragma once

#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

// Unnamed class of an object embedded in TreasureBox (+0xc0), derived from the AI tree variable
// root class (own RTTI typeInfo at GOT 0x7102583e48). Placeholder name = vtable address
// (0x710242cd08; D2 is a shared empty function, D0 0x71005ce834, RTTI 0x71005ce70c / 0x71005ce7d8).
class Unk_710242cd08 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_710242cd08, Unk_71025afb58)
public:
    u64 _8 = 0;
    Unk_71025afb58* _10 = nullptr;  // deleted by ~TreasureBox
};
KSYS_CHECK_SIZE_NX150(Unk_710242cd08, 0x18);

namespace uking::ai {

class TreasureBox : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TreasureBox, ksys::act::ai::Ai)
public:
    explicit TreasureBox(const InitArg& arg);
    ~TreasureBox() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool handleMessage_(const ksys::Message* message) override;

    // map_unit_param at offset 0x38
    const int* mSharpWeaponJudgeType_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mDropActor_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mDropTable_m{};
    // aitree_variable at offset 0x60
    bool* mIsOpenTreasureBox_a{};
    // aitree_variable at offset 0x68
    bool* mIsSetupDropActor_a{};
    // aitree_variable at offset 0x70
    sead::SafeString* mDropActorName_a{};
    // aitree_variable at offset 0x78
    void* mSharpWeaponAddParam_a{};
    Unk_7102450828 _80{0x1800005};
    Unk_710242cd08 _c0;
};
KSYS_CHECK_SIZE_NX150(TreasureBox, 0xd8);

}  // namespace uking::ai
