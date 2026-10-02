#include "Game/AI/Behavior/behaviorPlayerTriggerNoise.h"

namespace uking::behavior {

PlayerTriggerNoise::PlayerTriggerNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerTriggerNoise::m9() {}

void PlayerTriggerNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
