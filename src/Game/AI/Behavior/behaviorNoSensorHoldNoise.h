#pragma once

#include "Game/AI/Behavior/behaviorNoiseBase.h"

namespace uking::behavior {

class NoSensorHoldNoise : public NoiseBase {
    SEAD_RTTI_OVERRIDE(NoSensorHoldNoise, NoiseBase)
public:
    explicit NoSensorHoldNoise(const InitArg& arg);
    void m8() override;

};
KSYS_CHECK_SIZE_NX150(NoSensorHoldNoise, 0x40);

}  // namespace uking::behavior
