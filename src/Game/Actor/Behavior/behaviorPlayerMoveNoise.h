#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerMoveNoise : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerMoveNoise, ksys::act::ai::Behavior)
public:
    explicit PlayerMoveNoise(const InitArg& arg);
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mNoiseValue_s{};
    /* 0x30 */ const float* mMaxSpeed_s{};
    /* 0x38 */ const float* mMaxNoise_s{};
    /* 0x40 */ const bool* mIsVec3_s{};
};
KSYS_CHECK_SIZE_NX150(PlayerMoveNoise, 0x48);

}  // namespace uking::behavior
