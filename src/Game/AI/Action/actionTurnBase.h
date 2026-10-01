#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class TurnBase : public ActionEx {
    SEAD_RTTI_OVERRIDE(TurnBase, ActionEx)
public:
    explicit TurnBase(const InitArg& arg);
    ~TurnBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
    // static_param at offset 0x28
    const float* mFinRotate_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x40
    const bool* mIsFollowGround_s{};
    // static_param at offset 0x48
    const float* mRotMinSpeedRatio_s{};
    // static_param at offset 0x50
    const bool* mIsChangeable_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _60;
    // unknown object (0x24 bytes; methods 0x7100741034 / 0x7100741038 take it and the actor)
    u8 _6c[0x90 - 0x6c];
};

KSYS_CHECK_SIZE_NX150(TurnBase, 0x90);

}  // namespace uking::action
