#pragma once

#include "Game/AI/Behavior/behaviorNoiseBase.h"

namespace uking::behavior {

class NoSensorBombLandNoise : public NoiseBase {
    SEAD_RTTI_OVERRIDE(NoSensorBombLandNoise, NoiseBase)
public:
    explicit NoSensorBombLandNoise(const InitArg& arg);
    ~NoSensorBombLandNoise() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    f32 m14() override;

    /* 0x40 */ const int* mNoNoiseFrame_s{};
    /* 0x48 */ const float* mLandNoiseValue_s{};
    /* 0x50 */ const float* mNoiseSpeed_s{};
    /* 0x58 */ f32 _58 = 0.0f;
    /* 0x5c */ u32 _5c = 0;
    /* 0x60 */ bool _60 = false;
    /* 0x61 */ bool _61 = false;
};
KSYS_CHECK_SIZE_NX150(NoSensorBombLandNoise, 0x68);

}  // namespace uking::behavior
