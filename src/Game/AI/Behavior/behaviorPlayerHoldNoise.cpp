#include "Game/AI/Behavior/behaviorPlayerHoldNoise.h"

namespace uking::behavior {

PlayerHoldNoise::PlayerHoldNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerHoldNoise::m8() {}

void PlayerHoldNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
