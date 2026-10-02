#include "Game/AI/Behavior/behaviorTriggerNoise.h"

namespace uking::behavior {

TriggerNoise::TriggerNoise(const InitArg& arg) : Noise(arg) {}

void TriggerNoise::m7() {
    Noise::m7();
    if (!_100 && !_101) {
        sub_710062E9F0();
        sub_710062DF30();
        _101 = true;
    }
    _100 = false;
}

void TriggerNoise::m8() {
    Noise::m8();
    _100 = true;
    _101 = false;
    sub_710062E9F8();
}

}  // namespace uking::behavior
