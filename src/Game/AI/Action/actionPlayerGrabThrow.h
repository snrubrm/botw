#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGrabThrow : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGrabThrow, PlayerAction)
public:
    explicit PlayerGrabThrow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // 0x71007f00d0: moves the grabbed child along the player's facing by the throw speed, then resets the grab state.
    void sub_71007F00D0();

    // static_param at offset 0x20
    const float* mOverThrowSpeedYB_s{};
    // static_param at offset 0x28
    const float* mOverThrowSpeedFB_s{};
    // static_param at offset 0x30
    const float* mOverThrowSpeedYL_s{};
    // static_param at offset 0x38
    const float* mOverThrowSpeedFL_s{};
    // static_param at offset 0x40
    const float* mOverThrowInertiaRate_s{};
};

}  // namespace uking::action
