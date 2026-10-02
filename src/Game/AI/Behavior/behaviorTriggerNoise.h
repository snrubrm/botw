#pragma once

#include "Game/AI/Behavior/behaviorNoise.h"

namespace uking::behavior {

class TriggerNoise : public Noise {
    SEAD_RTTI_OVERRIDE(TriggerNoise, Noise)
public:
    explicit TriggerNoise(const InitArg& arg);
    void m7() override;
    void m8() override;

    /* 0x100 */ bool _100 = false;
    /* 0x101 */ bool _101 = false;
};
KSYS_CHECK_SIZE_NX150(TriggerNoise, 0x108);

}  // namespace uking::behavior
