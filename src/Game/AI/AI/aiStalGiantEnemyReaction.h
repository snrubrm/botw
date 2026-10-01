#pragma once

#include "Game/AI/AI/aiForestGiantReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalGiantEnemyReaction : public ForestGiantReaction {
    SEAD_RTTI_OVERRIDE(StalGiantEnemyReaction, ForestGiantReaction)
public:
    explicit StalGiantEnemyReaction(const InitArg& arg);
    ~StalGiantEnemyReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m37() override;
    void m40(ksys::act::ai::InlineParamPack* params) override;
    void m41(ksys::act::ai::InlineParamPack* params) override { m40(params); }

protected:
};

}  // namespace uking::ai
