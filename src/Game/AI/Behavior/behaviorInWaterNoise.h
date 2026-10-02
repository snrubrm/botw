#pragma once

#include "Game/AI/Behavior/behaviorNoise.h"

namespace uking::behavior {

class InWaterNoise : public Noise {
    SEAD_RTTI_OVERRIDE(InWaterNoise, Noise)
public:
    explicit InWaterNoise(const InitArg& arg);
    ~InWaterNoise() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(InWaterNoise, 0x100);

}  // namespace uking::behavior
