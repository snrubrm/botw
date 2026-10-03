#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerRideJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerRideJump, PlayerAction)
public:
    explicit PlayerRideJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // 0x710080d120 (out of line): applies the horse velocity plus the ladder displacement to the character controller.
    void sub_710080D120();

    // static_param at offset 0x20
    const float* mRideOffsetPosY_s{};
    // static_param at offset 0x28
    const float* mRideOffsetPosXZ_s{};
    // static_param at offset 0x30
    const float* mRideJumpTime_s{};
};

}  // namespace uking::action
