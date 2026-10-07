#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "Game/AI/aiPriestBossPhaseMembers.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseFourth : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseFourth, PriestBossPhase)
public:
    explicit PriestBossPhaseFourth(const InitArg& arg);
    ~PriestBossPhaseFourth() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void m34() override {}
    void m35() override {}
    bool m36() override { return PriestBossPhase::m36(); }
    bool m37(f32* x) override;
    Flag m38() override { return Flag::_3; }
    void m39() override {}

    void sub_710052A63C();

protected:
    // static_param at offset 0x80
    const int* mSimAtkMax_s{};
    // static_param at offset 0x88
    const int* mBowEquipMax_s{};
    // static_param at offset 0x90
    const float* mRespawnSpan_s{};
    /* 0x98 */ Unk_7102451070 _98;
    /* 0x3c8 */ Unk_7102451050 _3c8;
    /* 0x5d0 */ bool _5d0 = false;
};

KSYS_CHECK_SIZE_NX150(PriestBossPhaseFourth, 0x5d8);

}  // namespace uking::ai
