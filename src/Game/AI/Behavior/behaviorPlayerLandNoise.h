#pragma once

#include "Game/AI/Behavior/behaviorPlayerLandNoiseBase.h"

namespace uking::behavior {

class PlayerLandNoise : public PlayerLandNoiseBase {
    SEAD_RTTI_OVERRIDE(PlayerLandNoise, PlayerLandNoiseBase)
public:
    explicit PlayerLandNoise(const InitArg& arg);
    ~PlayerLandNoise() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    f32 m14() override;

};
KSYS_CHECK_SIZE_NX150(PlayerLandNoise, 0x108);

}  // namespace uking::behavior
