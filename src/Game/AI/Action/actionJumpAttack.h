#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpAttack, ksys::act::ai::Action)
public:
    explicit JumpAttack(const InitArg& arg);
    ~JumpAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m32(f32 a, f32 b);
    virtual f32 m33();

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mJumpHeight_s{};
    // static_param at offset 0x40
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x48
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x50
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x58
    const bool* mIsForceGuardBreak_s{};
    Unk_7102451ba0 _60;
    ksys::VFRValue _88;
    f32 _94 = 0;
    sead::Vector3f _98 = sead::Vector3f::zero;
    bool _a4 = false;
};

}  // namespace uking::action
