#pragma once

#include "Game/Actor/Behavior/behaviorPlayerLandNoiseBase.h"

namespace uking::behavior {

class PlayerLandNoise : public PlayerLandNoiseBase {
    SEAD_RTTI_OVERRIDE(PlayerLandNoise, PlayerLandNoiseBase)
public:
    explicit PlayerLandNoise(const InitArg& arg);
    ~PlayerLandNoise() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    f32 m14() override;

};
KSYS_CHECK_SIZE_NX150(PlayerLandNoise, 0x108);

}  // namespace uking::behavior
