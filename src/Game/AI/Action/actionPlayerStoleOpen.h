#pragma once

#include <gfx/seadColor.h>

#include "Game/AI/Action/actionPlayerStoleOpenEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStoleOpen : public PlayerStoleOpenEx {
    SEAD_RTTI_OVERRIDE(PlayerStoleOpen, PlayerStoleOpenEx)
public:
    explicit PlayerStoleOpen(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const float* mEnlargeSpd_s{};
    f32 _e0 = 0;
    sead::Color4f _e4{0, 0, 0, 0};
};

}  // namespace uking::action
