#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::as {
class ASList;
}

namespace uking::action {

s32 sub_710080C324(f32* timer, bool grounded, sead::Vector3f* previous_velocity,
                 const sead::Vector3f& velocity);

class PlayerRideHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerRideHorse, ksys::act::ai::Action)
public:
    explicit PlayerRideHorse(const InitArg& arg);
    ~PlayerRideHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_7100808F88();
    void sub_71008093A0();
    void sub_710080A224();
    void sub_710080B208(ksys::as::ASList* list, f32 rate);

    // static_param at offset 0x20
    const int* mAccelerateInputDelayGear0_s{};
    // static_param at offset 0x28
    const int* mAccelerateInputDelayGear1_s{};
    // static_param at offset 0x30
    const int* mAccelerateInputDelayGear2_s{};
    // static_param at offset 0x38
    const int* mAccelerateInputDelayGear3_s{};
    // static_param at offset 0x40
    const int* mAccelerateInputDelayGearTop_s{};
    // static_param at offset 0x48
    const int* mAccInputIgnoreFramesGear0_s{};
    // static_param at offset 0x50
    const int* mAccInputIgnoreFramesGear1_s{};
    // static_param at offset 0x58
    const int* mAccInputIgnoreFramesGear2_s{};
    // static_param at offset 0x60
    const int* mAccInputIgnoreFramesGear3_s{};
    // static_param at offset 0x68
    const int* mAccInputIgnoreFramesGearTop_s{};
    // static_param at offset 0x70
    const float* mDecelerateInputThreshold_s{};
    // static_param at offset 0x78
    const float* mStopInputFrames_s{};
    // static_param at offset 0x80
    const float* mAccelerateInputThreshold_s{};
    // static_param at offset 0x88
    const float* mMoveBackInputThreshold_s{};
    // static_param at offset 0x90
    const float* mStickXClampAtGear0_s{};
    // static_param at offset 0x98
    const float* mTurnStickXInputThreshold_s{};
    // static_param at offset 0xa0
    const float* mConstraintBreakThreshold_s{};
    // dynamic_param at offset 0xa8
    bool* mHasToPlayRidingOnAS_d{};
    f32 _b0 = 0.0f;
    f32 _b4 = 0.0f;
    f32 _b8 = 0.0f;
    f32 _bc = 0.075f;
    f32 _c0 = 0.15f;
    f32 _c4 = 0.0f;
    f32 _c8 = 0.0f;
    f32 _cc = 2.0f;
    s32 _d0 = 0;
    sead::Vector2f _d4{0.0f, 0.0f};
    sead::Vector2f _dc{0.0f, 0.0f};
    f32 _e4 = 0.0f;
    sead::Vector3f _e8 = sead::Vector3f::zero;
    sead::Vector3f _f4 = sead::Vector3f::zero;
    f32 _100 = 0.0f;
    u16 _104 = 0;
};
KSYS_CHECK_SIZE_NX150(PlayerRideHorse, 0x108);

}  // namespace uking::action
