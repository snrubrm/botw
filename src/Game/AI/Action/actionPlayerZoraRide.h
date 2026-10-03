#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerZoraRide : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerZoraRide, PlayerAction)
public:
    explicit PlayerZoraRide(const InitArg& arg);
    ~PlayerZoraRide() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLowerAngleWaitTime_s{};
    // static_param at offset 0x28
    const float* mAimAngleAddApplyAngle_s{};
    // static_param at offset 0x30
    const float* mAimAngleAdd_s{};
    // static_param at offset 0x38
    const float* mAimAngleAddApplySpeed_s{};
    bool _40 = false;
    f32 _44 = 0.0f;
    f32 _48 = 0.0f;
    f32 _4c = -1.0f;

};
KSYS_CHECK_SIZE_NX150(PlayerZoraRide, 0x50);

}  // namespace uking::action
