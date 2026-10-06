#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildArrowRain : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildArrowRain, ksys::act::ai::Action)
public:
    explicit BowChildArrowRain(const InitArg& arg);
    ~BowChildArrowRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mRainMax_s{};
    // static_param at offset 0x28
    const float* mMoveSpeed_s{};
    // static_param at offset 0x30
    const float* mMoveHeight_s{};
    // static_param at offset 0x38
    const float* mWaitTime_s{};
    // static_param at offset 0x40
    const float* mMoveCountNum_s{};
    // static_param at offset 0x48
    const float* mMoveRange_s{};
    // static_param at offset 0x50
    const float* mMoveOffsetBase_s{};
    // static_param at offset 0x58
    const float* mRotateRate_s{};
    // static_param at offset 0x60
    const float* mRotateStepMax_s{};
    // static_param at offset 0x68
    const float* mAngleToTarget_s{};
    // static_param at offset 0x70
    const float* mTargetOffsetBase_s{};
    // static_param at offset 0x78
    const float* mRainScale_s{};
    // static_param at offset 0x80
    const float* mToTargetTime_s{};
    // dynamic_param at offset 0x88
    int* mID_d{};
    // dynamic_param at offset 0x90
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x98
    bool* mIsIgnoreHightOffset_d{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mMoveTargetPos_d{};
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mParentActor_d{};

    s32 _b8 = 0;
    s32 _bc = 0;
    f32 _c0 = 0;
    f32 _c4 = 0;
    f32 _c8 = 0;
    f32 _cc = 0;
    bool _d0 = false;
    bool _d1 = false;
    bool _d2 = false;
    s32 _d4 = 0;
    s32 _d8 = 0;
    u8 _dc[0x24];
    u64 _100 = 0;
    u64 _108 = 0;
    s32 _110 = 0;
    u8 _114[0x18];
    // Placeholder layout of the block at 0x12c (0x408 bytes, zero-initialised as a whole).
    struct Unk12c {
        u8 _0[0x3c0];
        sead::Vector3f _3c0{0, 0, 0};
        sead::Vector3f _3cc{0, 0, 0};
        sead::Vector2f _3d8[6]{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    };
    Unk12c _12c{};
};

}  // namespace uking::action
