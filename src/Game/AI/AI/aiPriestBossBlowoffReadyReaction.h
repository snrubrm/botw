#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBlowoffReadyReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossBlowoffReadyReaction, ksys::act::ai::Ai)
public:
    explicit PriestBossBlowoffReadyReaction(const InitArg& arg);
    ~PriestBossBlowoffReadyReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_7100510E80();

protected:
    // aitree_variable at offset 0x38
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
