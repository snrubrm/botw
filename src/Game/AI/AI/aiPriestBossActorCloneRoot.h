#pragma once

#include "Game/AI/AI/aiPriestBossActorNormalRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorCloneRoot : public PriestBossActorNormalRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorCloneRoot, PriestBossActorNormalRoot)
public:
    explicit PriestBossActorCloneRoot(const InitArg& arg);
    ~PriestBossActorCloneRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m36() override;

protected:
    // static_param at offset 0x88
    sead::SafeString mDisappearXLinkEventKey_s{};
};

}  // namespace uking::ai
