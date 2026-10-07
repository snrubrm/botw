#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseThird : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseThird, PriestBossPhase)
public:
    explicit PriestBossPhaseThird(const InitArg& arg);
    ~PriestBossPhaseThird() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35() override;
    bool m36() override { return PriestBossPhase::m36(); }
    bool m37(f32* x) override;
    Flag m38() override { return Flag::_2; }
    void m39() override {}

protected:
    // static_param at offset 0x80
    const int* mBreakIronBallCount_s{};
    Unk_7102415900 _88{mActor, 0x80000dd};
};
KSYS_CHECK_SIZE_NX150(PriestBossPhaseThird, 0xb8);

}  // namespace uking::ai
