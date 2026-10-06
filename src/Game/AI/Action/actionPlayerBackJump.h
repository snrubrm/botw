#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class Player;
}

// 0x71007d86b4 (placeholder name; unnamed in the CSV, called from Player::m81 and others): whether the player's
// current AS (slot 1, bank 1) is one of the horse call sequences.
bool sub_71007D86B4(ksys::act::Player* player);

namespace uking::action {

class PlayerBackJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerBackJump, PlayerAction)
public:
    explicit PlayerBackJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;
    bool isFinished() const override;

protected:
    bool sub_71007D8358() const;
    void calc_() override;

    // static_param at offset 0x20
    const float* mBJSpeedF_s{};
    // static_param at offset 0x28
    const float* mBJHeight_s{};
    // static_param at offset 0x30
    const float* mNoDamageTime_s{};
    // static_param at offset 0x38
    const float* mJustAvoidTime_s{};
    // static_param at offset 0x40
    const float* mForceSlowTime_s{};
    // static_param at offset 0x48
    const float* mMySlowStartFrame_s{};
    // dynamic_param at offset 0x50
    bool* mEnableSwordInput_d{};
};

}  // namespace uking::action
