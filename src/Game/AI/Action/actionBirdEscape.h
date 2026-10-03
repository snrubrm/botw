#pragma once

#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BirdEscape : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BirdEscape, ksys::act::ai::Action)
public:
    explicit BirdEscape(const InitArg& arg);
    ~BirdEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const float* mMoveSpeedMax_s{};
        // static_param at offset 0x28
        const float* mMoveSpeedMin_s{};
        // static_param at offset 0x30
        const float* mTurnSpeed_s{};
        // static_param at offset 0x38
        const float* mInterpolateFrameForMaxSpeed_s{};
        // static_param at offset 0x40
        const float* mTargetEscapeWidthMax_s{};
        // static_param at offset 0x48
        const float* mTargetEscapeWidthMin_s{};
        // static_param at offset 0x50
        const float* mTargetHeightMax_s{};
        // static_param at offset 0x58
        const float* mTargetHeightMin_s{};
        // static_param at offset 0x60
        const float* mTargetTurnAngle_s{};
        // static_param at offset 0x68
        const float* mContinueEscapeDistanceXZ_s{};
        // static_param at offset 0x70
        const float* mAdditionalWidth_s{};
        // static_param at offset 0x78
        const float* mTargetUpperAngle_s{};
        // static_param at offset 0x80
        const float* mStartReduceHeightRate_s{};
    };
    Params mParams;
    ksys::act::CCAccessor _88;
    u8 _90[0x30];
    u64 _c0 = 0;
    f32 _c8 = 0.0f;
    ksys::VFRValue _cc{0.0f};
    ksys::VFRValue _d8;
    f32 _e4 = 0.0f;
    s32 _e8 = 0;
    s32 _ec = 0;
    f32 _f0 = 0.0f;
    f32 _f4 = 0.0f;
    s32 _f8 = 0;
    f32 _fc = 1.0f;
    f32 _100 = 0.0f;
    bool _104 = false;
    u8 _105[0x3];
};
KSYS_CHECK_SIZE_NX150(BirdEscape, 0x108);

}  // namespace uking::action
