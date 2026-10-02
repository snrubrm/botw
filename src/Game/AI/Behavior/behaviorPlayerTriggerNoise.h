#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerTriggerNoise : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerTriggerNoise, ksys::act::ai::Behavior)
public:
    explicit PlayerTriggerNoise(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mNoiseValue_s{};
    /* 0x30 */ bool _30 = true;
};
KSYS_CHECK_SIZE_NX150(PlayerTriggerNoise, 0x38);

}  // namespace uking::behavior
