#include "Game/AI/Behavior/behaviorNoSensorWaterInNoise.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

NoSensorWaterInNoise::NoSensorWaterInNoise(const InitArg& arg) : NoiseBase(arg) {}

// NON_MATCHING: Actor::_68f is read through sead::Atomic (volatile with MATCHING_HACK_NX_CLANG); the
// original reads it like a plain byte (both loads speculated / an explicit != 0)
void NoSensorWaterInNoise::m7() {
    NoiseBase::m7();
    const bool in_water = mActor->get68f();
    if (in_water && !_39)
        sub_710062E9F8();
    else
        sub_710062E9F0();
    _39 = in_water;
}

void NoSensorWaterInNoise::m8() {
    _39 = false;
}

}  // namespace uking::behavior
