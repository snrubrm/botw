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

    struct Params {
        const float* mNoiseWait_s{};
        const float* mNoiseCourbette_s{};
        const float* mNoiseDamage_s{};
        const float* mNoiseMoveShift_s{};
        const float* mNoiseMoveBack_s{};
        const float* mNoiseGear1_s{};
        const float* mNoiseGear2_s{};
        const float* mNoiseGear3_s{};
        const float* mNoiseGearTop_s{};
    };
    /* 0x28 */ Params mParams;
};
KSYS_CHECK_SIZE_NX150(HorseNoise, 0x70);

}  // namespace uking::behavior
