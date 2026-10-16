#include "Game/Actor/Behavior/behaviorNoSensorWaterInNoise.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

NoSensorWaterInNoise::NoSensorWaterInNoise(const InitArg& arg) : NoiseBase(arg) {}

void NoSensorWaterInNoise::calc() {
    NoiseBase::calc();
    const bool in_water = mActor->get68f();
    if (in_water && !_39)
        sub_710062E9F8();
    else
        sub_710062E9F0();
    _39 = in_water;
}

void NoSensorWaterInNoise::enter() {
    _39 = false;
}

}  // namespace uking::behavior
