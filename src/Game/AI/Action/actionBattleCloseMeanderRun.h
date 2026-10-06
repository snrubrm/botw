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
    f32 _c0{};
    f32 _c4{};
    f32 _c8{};
    f32 _cc{};
    f32 _d0{};
    sead::Vector3f _d4{0, 0, 0};
    sead::Vector3f _e0{0, 0, 0};
    sead::Vector3f _ec{0, 0, 0};
    bool _f8{};
    bool _f9{};
    bool _fa{};
};

}  // namespace uking::action
