#pragma once

#include "Game/AI/AI/aiPriestBossPhase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseFirst : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseFirst, PriestBossPhase)
public:
    explicit PriestBossPhaseFirst(const InitArg& arg);
    ~PriestBossPhaseFirst() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m36() override;
    Flag m38() override { return Flag::_0; }
    void m39() override;

protected:
    bool _7c = false;
};
KSYS_CHECK_SIZE_NX150(PriestBossPhaseFirst, 0x80);

}  // namespace uking::ai
