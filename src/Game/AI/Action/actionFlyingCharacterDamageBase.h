#pragma once

#include "Game/AI/Action/actionFlyingCharacterReaction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterDamageBase : public FlyingCharacterReaction {
    SEAD_RTTI_OVERRIDE(FlyingCharacterDamageBase, FlyingCharacterReaction)
public:
    explicit FlyingCharacterDamageBase(const InitArg& arg);
    ~FlyingCharacterDamageBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100130868 (declared only): out of line in the original.
    void sub_7100130868(ksys::phys::CharacterController* controller, const sead::Vector3f& dir);
    // 0x7100130aa4: the HitImpactForce parameter for the current damage (sword / spear kind, small / large
    // damage kind) times the damage manager's factor (without a manager: SmallSwordS).
    f32 sub_7100130AA4();
    void calc_() override;
    void m33() override;
    void m34(ksys::phys::CharacterController* controller) override;
    void m36() override;
    void m37(ksys::phys::CharacterController* controller) override;

    // static_param at offset 0x70
    const float* mHitImpactForceSmallSwordS_s{};
    // static_param at offset 0x78
    const float* mHitImpactForceSmallSwordL_s{};
    // static_param at offset 0x80
    const float* mHitImpactForceLargeSwordS_s{};
    // static_param at offset 0x88
    const float* mHitImpactForceLargeSwordL_s{};
    // static_param at offset 0x90
    const float* mHitImpactForceSpearS_s{};
    // static_param at offset 0x98
    const float* mHitImpactForceSpearL_s{};
    // static_param at offset 0xa0
    const float* mRiseSpeed_s{};
    // static_param at offset 0xa8
    const float* mLastSpeedRatio_s{};
    // static_param at offset 0xb0
    const float* mPosReduceRatioOnGround_s{};
    // static_param at offset 0xb8
    const float* mRotReduceRatioOnGround_s{};
    // static_param at offset 0xc0
    const bool* mIsCheckFallASFinished_s{};
    // static_param at offset 0xc8
    const bool* mIsIgnoreSameAS4Fall_s{};
    // static_param at offset 0xd0
    const bool* mIsIgnoreSameAS4OnGround_s{};
    // static_param at offset 0xd8
    sead::SafeString mFallAS_s{};
    // static_param at offset 0xe8
    sead::SafeString mOnGroundAS_s{};
};

}  // namespace uking::action
