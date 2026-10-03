#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGuidedMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGuidedMove, PlayerAction)
public:
    explicit PlayerGuidedMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual bool m33(sead::Vector3f* pos) { return false; }

    // static_param at offset 0x20
    const float* mDecSpdDist_s{};
    // dynamic_param at offset 0x28
    float* mStickValue_d{};
    // static_param at offset 0x30
    const float* mForceTurnDist_s{};
    f32 _38 = 1.0f;
    f32 _3c = 1.0f;
    f32 _40 = 99999.0f;
    f32 _44 = 0.0f;
    bool _48 = true;
    sead::Vector3f _4c = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(PlayerGuidedMove, 0x58);

}  // namespace uking::action
