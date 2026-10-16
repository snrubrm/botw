#include "Game/Actor/Behavior/behaviorNoSensorHoldNoise.h"

namespace uking::behavior {

NoSensorHoldNoise::NoSensorHoldNoise(const InitArg& arg) : NoiseBase(arg) {}

void NoSensorHoldNoise::enter() {
    sub_710062E9F8();
}

}  // namespace uking::behavior
