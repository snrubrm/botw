#pragma once

#include "Game/AI/Behavior/behaviorNoise.h"

namespace uking::behavior {

// CSV name: PlayerLandNoise (the base of the PlayerLandNoise behavior).
class PlayerLandNoiseBase : public Noise {
    SEAD_RTTI_OVERRIDE(PlayerLandNoiseBase, Noise)
public:
    explicit PlayerLandNoiseBase(const InitArg& arg);
    void m7() override;
    void m8() override;

    /* 0x100 */ bool _100 = false;
};

}  // namespace uking::behavior
