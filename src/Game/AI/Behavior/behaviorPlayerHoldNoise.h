#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerHoldNoise : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerHoldNoise, ksys::act::ai::Behavior)
public:
    explicit PlayerHoldNoise(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mNoiseValue_s{};
};
KSYS_CHECK_SIZE_NX150(PlayerHoldNoise, 0x30);

}  // namespace uking::behavior
