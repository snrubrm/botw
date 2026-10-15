#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class JumpMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpMove, ksys::act::ai::Action)
public:
    explicit JumpMove(const InitArg& arg);
    ~JumpMove() override;

    bool isFinished() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPreJumpWait_s{};
    // static_param at offset 0x28
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x30
    const float* mMinMoveSpeed_s{};
    // static_param at offset 0x38
    const float* mRandAngleLimit_s{};
    // static_param at offset 0x40
    const float* mJumpHeight_s{};
    // static_param at offset 0x48
    sead::SafeString mASKey_s{};
    ksys::Timer _58;
    sead::Vector3f _64;
    sead::Vector3f _70;
    f32 _7c = 0.0f;
    f32 _80 = 0.0f;
    s32 _84 = 0;
    bool _88 = false;
    bool _89 = false;
    bool _8a = false;
};
KSYS_CHECK_SIZE_NX150(JumpMove, 0x90);

}  // namespace uking::action
