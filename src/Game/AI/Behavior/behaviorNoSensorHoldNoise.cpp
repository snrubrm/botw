#include "Game/AI/Behavior/behaviorNoSensorHoldNoise.h"

namespace uking::behavior {

NoSensorHoldNoise::NoSensorHoldNoise(const InitArg& arg) : NoiseBase(arg) {}

void NoSensorHoldNoise::m8() {
    sub_710062E9F8();
}

}  // namespace uking::behavior
