#include "Game/AI/Behavior/behaviorInWaterNoise.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

InWaterNoise::InWaterNoise(const InitArg& arg) : Noise(arg) {}

InWaterNoise::~InWaterNoise() = default;

// NON_MATCHING: Actor::_68f is read through sead::Atomic (volatile with MATCHING_HACK_NX_CLANG); the
// original reads it like a plain byte (both loads speculated / an explicit != 0)
void InWaterNoise::m7() {
    if (!mActor->get690() && mActor->get68f())
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
