#include "Game/AI/Behavior/behaviorInWaterNoise.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

InWaterNoise::InWaterNoise(const InitArg& arg) : Noise(arg) {}

InWaterNoise::~InWaterNoise() = default;

void InWaterNoise::m7() {
    if ((!mActor->get690()) & (mActor->get68f() != 0))
        sub_710062E9F8();
    else
        sub_710062E9F0();
    Noise::m7();
}

void InWaterNoise::m8() {
    Noise::m8();
}

void InWaterNoise::m9() {
    Noise::m9();
}

void InWaterNoise::loadParams() {
    Noise::loadParams();
}

}  // namespace uking::behavior
