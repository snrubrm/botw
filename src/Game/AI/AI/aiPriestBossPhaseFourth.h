#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
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
    void loadParams_() override;

    void m34() override {}
    void m35() override {}
    bool m36() override { return PriestBossPhase::m36(); }
    Flag m38() override { return Flag::_3; }
    void m39() override {}

protected:
    // static_param at offset 0x80
    const int* mSimAtkMax_s{};
    // static_param at offset 0x88
    const int* mBowEquipMax_s{};
    // static_param at offset 0x90
    const float* mRespawnSpan_s{};
};

}  // namespace uking::ai
