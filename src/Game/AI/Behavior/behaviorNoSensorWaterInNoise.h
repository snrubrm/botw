#pragma once

#include "Game/AI/Behavior/behaviorNoiseBase.h"

namespace uking::behavior {

class NoSensorWaterInNoise : public NoiseBase {
    SEAD_RTTI_OVERRIDE(NoSensorWaterInNoise, NoiseBase)
public:
    explicit NoSensorWaterInNoise(const InitArg& arg);
    void m7() override;
    void m8() override;

    /* 0x39 */ bool _39 = false;
};
KSYS_CHECK_SIZE_NX150(NoSensorWaterInNoise, 0x40);

}  // namespace uking::behavior
