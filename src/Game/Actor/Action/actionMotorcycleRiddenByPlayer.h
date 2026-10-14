#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleRiddenByPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MotorcycleRiddenByPlayer, ksys::act::ai::Action)
public:
    explicit MotorcycleRiddenByPlayer(const InitArg& arg);
    ~MotorcycleRiddenByPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;
    bool updateForPreDelete() override;

protected:
    void calc_() override;
    void calcTerrorVelocityStuff(f32 speed, const sead::Vector3f* dir);

    // static_param at offset 0x20
    const float* mCrashVelocityThreshold_s{};
    // static_param at offset 0x28
    const float* mRideOnDelayFrames_s{};
    // static_param at offset 0x30
    const float* mFallThresholdForThrowOff_s{};
    // static_param at offset 0x38
    const float* mCrashVelocityDeltaThreshold_s{};
    // static_param at offset 0x40
    const float* mChargeVelocityThreshold_s{};
    // static_param at offset 0x48
    const float* mDriftCutGrassRange_s{};
    // static_param at offset 0x50
    const float* mDriftCutGrassIntensity_s{};
    // static_param at offset 0x58
    const float* mCutLowTreeVelocityThreshold_s{};
    // static_param at offset 0x60
    const float* mCutLowTreeVelocitySize_s{};
    // static_param at offset 0x68
    const float* mTerrorVelocityThreshold1_s{};
    // static_param at offset 0x70
    const float* mTerrorVelocityThreshold2_s{};
    // static_param at offset 0x78
    const float* mTerrorVelocityThreshold3_s{};
    // static_param at offset 0x80
    const float* mTerrorVelocityThreshold4_s{};
    // static_param at offset 0x88
    const float* mTerrorRadius_s{};
    // static_param at offset 0x90
    const float* mTerrorOffsetDistanceSec_s{};
    // static_param at offset 0x98
    const float* mForbidSpinturnAngleRange_s{};
    // static_param at offset 0xa0
    const float* mPermitManualWheelieAngleRange_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mAttackChargeBoneOffset_s{};
    /* 0x0b0 */ f32 _b0 = 0;
    /* 0x0b4 */ f32 _b4 = -1.0f;
    /* 0x0b8 */ f32 _b8 = 0;
    /* 0x0bc */ f32 _bc = 0;
    /* 0x0c0 */ ksys::act::AITerror _c0{mActor};
    /* 0x178 */ gsys::BoneAccessKey _178;
    /* 0x17c */ gsys::BoneAccessKey _17c;
    /* 0x180 */ gsys::BoneAccessKey _180;
    /* 0x184 */ bool _184 = false;
    /* 0x186 */ sead::BitFlag16 _186;
};
KSYS_CHECK_SIZE_NX150(MotorcycleRiddenByPlayer, 0x188);

}  // namespace uking::action
