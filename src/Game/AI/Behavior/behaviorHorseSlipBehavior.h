#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HorseSlipBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HorseSlipBehavior, ksys::act::ai::Behavior)
public:
    explicit HorseSlipBehavior(const InitArg& arg);
    ~HorseSlipBehavior() override;
    bool m6(sead::Heap* heap) override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100e613f4)
    void m8() override;  // not decompiled yet (0x7100e612f0)
    void m9() override;  // not decompiled yet (0x7100e61aa0)

    /* 0x28 */ const float* mSlipAngleDeg_s{};
    /* 0x30 */ const float* mSlipAngleDegGear1_s{};
    /* 0x38 */ const float* mSlipAngleDegGear2_s{};
    /* 0x40 */ const float* mSlipAngleDegGear3_s{};
    /* 0x48 */ const float* mSlipAngleDegGearTop_s{};
    /* 0x50 */ const float* mSlipEndAngleDeg_s{};
    /* 0x58 */ const float* mMaxSlipAngleDeg_s{};
    /* 0x60 */ const float* mSlipFramesThreshold_s{};
    /* 0x68 */ const float* mSlipValueThreshold_s{};
    /* 0x70 */ const float* mSlipRecoveryFactor_s{};
    /* 0x78 */ const float* mSlipVelocityMax_s{};
    /* 0x80 */ const float* mSlipVelocityAddScale_s{};
    /* 0x88 */ const float* mSlipSpeedAttn_s{};
    /* 0x90 */ const float* mLimitGear1FrameThreshold_s{};
    /* 0x98 */ f32 _98 = 0.0f;
    /* 0x9c */ u32 _9c = 0;
};
KSYS_CHECK_SIZE_NX150(HorseSlipBehavior, 0xa0);

}  // namespace uking::behavior
