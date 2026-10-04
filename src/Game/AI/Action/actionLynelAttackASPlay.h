#pragma once

#include "Game/AI/aiUnk_710070E434.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class LynelAttackASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LynelAttackASPlay, ksys::act::ai::Action)
public:
    explicit LynelAttackASPlay(const InitArg& arg);
    ~LynelAttackASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71001dec28: turns the actor towards `*mTargetPos_d` seen from `pos` (ASList turn speed, slot 9).
    void sub_71001DEC28(const sead::Vector3f& pos);
    // 0x71001df2e0: changeable timing (AS key 22 / ASList bank) and EndState handling.
    void sub_71001DF2E0();
    // 0x71001df3bc: reads the AS keys 41 / 47 / 43 into _1c0 / _1c4 / _1c8 / _1cc.
    void sub_71001DF3BC(const sead::Vector3f& pos);
    // 0x71001df63c / 0x71001df7d4: limit `*speed` so that the actor does not overshoot `*mTargetPos_d`
    // (nav mesh ray cast version / plain distance version).
    void sub_71001DF63C(f32* speed, const sead::Vector3f& pos);
    void sub_71001DF7D4(f32* speed, const sead::Vector3f& pos);
    // 0x71001df8dc: turns the controller towards `*mTargetPos_d` (rotation matrix `_1d0`).
    void sub_71001DF8DC(ksys::phys::CharacterController* controller, const sead::Vector3f& pos);
    // 0x71001dfa04: moves the controller along the actor's front.
    void sub_71001DFA04(ksys::phys::CharacterController* controller, const sead::Vector3f& pos);

    // inline-only in the original (name is a guess): decelerates the controller by `_1cc` per frame.
    void slowDown(ksys::phys::CharacterController* controller);

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mEndState_s{};
    // static_param at offset 0x30
    const int* mChangeableTiming_s{};
    // static_param at offset 0x38
    const float* mRotSpeed_s{};
    // static_param at offset 0x40
    const float* mSpeed_s{};
    // static_param at offset 0x48
    const float* mTransAccRatio_s{};
    // static_param at offset 0x50
    const float* mRotAccRatio_s{};
    // static_param at offset 0x58
    const float* mRange_s{};
    // static_param at offset 0x60
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x68
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x70
    const float* mJumpUpSpeedReduceRatio_s{};
    // static_param at offset 0x78
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x80
    const bool* mUseAnimeDriven_s{};
    // static_param at offset 0x88
    const bool* mIsCheckNavMesh_s{};
    // static_param at offset 0x90
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mTargetPos_d{};
    Unk_710070e434 _a8{mActor};
    u8 _1c0 = 0;
    f32 _1c4 = 0;
    f32 _1c8 = 0;
    f32 _1cc = 0;
    sead::Matrix33f _1d0;
};
KSYS_CHECK_SIZE_NX150(LynelAttackASPlay, 0x1f8);

}  // namespace uking::action
