#include "Game/AI/Behavior/behaviorNoSensorWaterInNoise.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

NoSensorWaterInNoise::NoSensorWaterInNoise(const InitArg& arg) : NoiseBase(arg) {}

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
