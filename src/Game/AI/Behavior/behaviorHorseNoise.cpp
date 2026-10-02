#include "Game/AI/Behavior/behaviorHorseNoise.h"

namespace uking::behavior {

// NON_MATCHING: the original tail-calls memset for the parameters (known clang difference)
HorseNoise::HorseNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseNoise::~HorseNoise() = default;

bool HorseNoise::m6(sead::Heap* heap) {
    return true;
}

void HorseNoise::m8() {}

void HorseNoise::m9() {}

void HorseNoise::loadParams() {
    getStaticParam(&mNoiseWait_s, "NoiseWait");
    getStaticParam(&mNoiseCourbette_s, "NoiseCourbette");
    getStaticParam(&mNoiseDamage_s, "NoiseDamage");
    getStaticParam(&mNoiseMoveShift_s, "NoiseMoveShift");
    getStaticParam(&mNoiseMoveBack_s, "NoiseMoveBack");
    getStaticParam(&mNoiseGear1_s, "NoiseGear1");
    getStaticParam(&mNoiseGear2_s, "NoiseGear2");
    getStaticParam(&mNoiseGear3_s, "NoiseGear3");
    getStaticParam(&mNoiseGearTop_s, "NoiseGearTop");
}

}  // namespace uking::behavior
