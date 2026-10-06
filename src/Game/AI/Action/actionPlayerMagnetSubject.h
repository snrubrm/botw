#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerMagnetSubject : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerMagnetSubject, PlayerAction)
public:
    explicit PlayerMagnetSubject(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;
    bool isFailed() const override;

protected:
    void calc_() override;

    // 0x71007fee10 (declared only; 1320 B, shared by enter_ and calc_).
    void sub_71007FEE10();

    // static_param at offset 0x20
    const float* mDRCEnergy_s{};
};

}  // namespace uking::action
