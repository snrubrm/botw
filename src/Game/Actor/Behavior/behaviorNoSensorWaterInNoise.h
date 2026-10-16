#pragma once

#include "Game/Actor/Behavior/behaviorNoiseBase.h"

namespace uking::behavior {

class NoSensorWaterInNoise : public NoiseBase {
    SEAD_RTTI_OVERRIDE(NoSensorWaterInNoise, NoiseBase)
public:
    explicit NoSensorWaterInNoise(const InitArg& arg);
    void calc() override;
    void enter() override;

    /* 0x39 */ bool _39 = false;
};
KSYS_CHECK_SIZE_NX150(NoSensorWaterInNoise, 0x40);

}  // namespace uking::behavior
