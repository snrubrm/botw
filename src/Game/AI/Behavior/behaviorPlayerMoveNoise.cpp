#include "Game/AI/Behavior/behaviorPlayerMoveNoise.h"

namespace uking::behavior {

PlayerMoveNoise::PlayerMoveNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerMoveNoise::m8() {}

void PlayerMoveNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxNoise_s, "MaxNoise");
    getStaticParam(&mIsVec3_s, "IsVec3");
}

}  // namespace uking::behavior
