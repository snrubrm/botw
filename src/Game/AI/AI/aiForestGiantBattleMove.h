#pragma once

#include "Game/AI/AI/aiWaitNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantBattleMove : public WaitNearTarget {
    SEAD_RTTI_OVERRIDE(ForestGiantBattleMove, WaitNearTarget)
public:
    explicit ForestGiantBattleMove(const InitArg& arg);
    ~ForestGiantBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const float* mAttackHeightMin_s{};
    // static_param at offset 0x70
    const float* mAttackHeightMax_s{};
    f32 _78{};
    s32 _7c{};
    s32 _80{};
};

}  // namespace uking::ai
