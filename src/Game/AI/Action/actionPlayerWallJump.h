#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerWallJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerWallJump, PlayerAction)
public:
    explicit PlayerWallJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // 0x7100823c4c (placeholder name): feeds the stick length and the turn angle into the AS controller.
    void sub_7100823C4C();

    // static_param at offset 0x20
    const float* mJumpHeight_s{};
    // static_param at offset 0x28
    const float* mJumpSpeedF_s{};
};

}  // namespace uking::action
