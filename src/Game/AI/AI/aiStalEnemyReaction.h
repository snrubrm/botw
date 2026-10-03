#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(StalEnemyReaction, EnemyDefaultReaction)
public:
    explicit StalEnemyReaction(const InitArg& arg);
    ~StalEnemyReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m37() override;
    void m40(ksys::act::ai::InlineParamPack* params) override;
    void m41(ksys::act::ai::InlineParamPack* params) override { m40(params); }
    void m43(ksys::act::ai::InlineParamPack* params) override { changeChild("ふっとび", params); }

protected:
};

}  // namespace uking::ai
