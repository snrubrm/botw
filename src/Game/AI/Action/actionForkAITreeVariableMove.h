#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAITreeVariableMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAITreeVariableMove, ksys::act::ai::Action)
public:
    explicit ForkAITreeVariableMove(const InitArg& arg);
    ~ForkAITreeVariableMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710005be70: with IsKeepDistFromGround, raises the destination's height by the keep distance
    // above the ground found below it.
    void sub_710005BE70();

    // static_param at offset 0x20
    const float* mArrivedRadius_s{};
    // static_param at offset 0x28
    const float* mTargetSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSlerpRate_s{};
    // static_param at offset 0x38
    const float* mKeepDistFromGround_s{};
    // static_param at offset 0x40
    const bool* mIsChangeable_s{};
    // static_param at offset 0x48
    const bool* mIsSuccessEndOnArrive_s{};
    // static_param at offset 0x50
    const bool* mIsKeepDistFromGround_s{};
    // aitree_variable at offset 0x58
    float* mTargetSpeed_a{};
    // aitree_variable at offset 0x60
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x68
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x70
    bool* mIsActive_a{};
    // aitree_variable at offset 0x78
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0x80
    sead::Vector3f* mFacePos_a{};
    sead::Vector3f _88{0.0f, 0.0f, 0.0f};
    u8 _94[0x18]{};
    s32 _ac = 0;
    bool _b0 = false;
    bool _b1 = false;
    u8 _b2[0x6];
};
KSYS_CHECK_SIZE_NX150(ForkAITreeVariableMove, 0xb8);

}  // namespace uking::action
