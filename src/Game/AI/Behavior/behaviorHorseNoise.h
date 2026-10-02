#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HorseNoise : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HorseNoise, ksys::act::ai::Behavior)
public:
    explicit HorseNoise(const InitArg& arg);
    ~HorseNoise() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100628fe8)

    /* 0x28 */ const float* mNoiseWait_s{};
    /* 0x30 */ const float* mNoiseCourbette_s{};
    /* 0x38 */ const float* mNoiseDamage_s{};
    /* 0x40 */ const float* mNoiseMoveShift_s{};
    /* 0x48 */ const float* mNoiseMoveBack_s{};
    /* 0x50 */ const float* mNoiseGear1_s{};
    /* 0x58 */ const float* mNoiseGear2_s{};
    /* 0x60 */ const float* mNoiseGear3_s{};
    /* 0x68 */ const float* mNoiseGearTop_s{};
};
KSYS_CHECK_SIZE_NX150(HorseNoise, 0x70);

}  // namespace uking::behavior
