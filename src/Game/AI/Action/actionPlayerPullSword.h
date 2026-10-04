#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerPullSword : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerPullSword, PlayerAction)
public:
    explicit PlayerPullSword(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    void sub_7100807630();
    // Declared only: locates the sword-pull actor.
    void sub_71008077FC();

    u64 _20 = 0;
    // static_param at offset 0x28
    const float* mLifeDecInterval1_s{};
    // static_param at offset 0x30
    const float* mLifeDecInterval2_s{};
    // static_param at offset 0x38
    const float* mLifeDecInterval3_s{};
    // static_param at offset 0x40
    const float* mLifeDecInterval4_s{};
    // static_param at offset 0x48
    const float* mLifeDecInterval5_s{};
    // static_param at offset 0x50
    const float* mInterruptInterval_s{};
    u64 _58 = 0;
    // static_param at offset 0x60
    const int* mSuccessLife_s{};
    s8 _68 = 0;

};
KSYS_CHECK_SIZE_NX150(PlayerPullSword, 0x70);

}  // namespace uking::action
