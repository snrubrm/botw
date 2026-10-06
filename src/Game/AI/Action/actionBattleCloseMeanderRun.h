#pragma once

#include "Game/AI/Action/actionBattleCloseMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMeanderRun : public BattleCloseMoveAction {
    SEAD_RTTI_OVERRIDE(BattleCloseMeanderRun, BattleCloseMoveAction)
public:
    explicit BattleCloseMeanderRun(const InitArg& arg);
    ~BattleCloseMeanderRun() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    f32 m35() override;
    virtual void m40();

    // static_param at offset 0xa8
    const float* mMeanderWidth_s{};
    // static_param at offset 0xb0
    const float* mMeanderSpeed_s{};
    // static_param at offset 0xb8
    const float* mJumpUpSpeedReduceRatio_s{};
    u8 _c0[0xc]{};
    f32 _cc{};
    u8 _d0[0x2a]{};
    bool _fa{};
};

}  // namespace uking::action
