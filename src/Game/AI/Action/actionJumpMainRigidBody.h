#pragma once

#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpMainRigidBody : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpMainRigidBody, ksys::act::ai::Action)
public:
    explicit JumpMainRigidBody(const InitArg& arg);
    ~JumpMainRigidBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPower_s{};
    // static_param at offset 0x28
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0x30
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0x38
    const float* mVibrateMemoryStep_s{};
    // static_param at offset 0x40
    const bool* mIsRotJumpDir_s{};
    // static_param at offset 0x48
    sead::SafeString mPostBoundReactionKeys_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mJumpDir_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x68
    void* mRefPosVibrateChecker_a{};
    Unk_71000b0800<Unk_71025b0578> _70;
    bool _78 = true;
    bool _79 = false;
    bool _7a = true;
    bool _7b = false;
    bool _7c = false;
};

}  // namespace uking::action
