#pragma once

#include "Game/Actor/Behavior/behaviorNoise.h"

namespace uking::behavior {

class InWaterNoise : public Noise {
    SEAD_RTTI_OVERRIDE(InWaterNoise, Noise)
public:
    explicit InWaterNoise(const InitArg& arg);
    ~InWaterNoise() override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(InWaterNoise, 0x100);

}  // namespace uking::behavior
