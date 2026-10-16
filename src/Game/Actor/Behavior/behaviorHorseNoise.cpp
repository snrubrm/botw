#include "Game/Actor/Behavior/behaviorHorseNoise.h"

namespace uking::behavior {

HorseNoise::HorseNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseNoise::~HorseNoise() = default;

bool HorseNoise::init_(sead::Heap* heap) {
    return true;
}

void HorseNoise::enter() {}

void HorseNoise::leave() {}

void HorseNoise::loadParams() {
    getStaticParam(&mParams.mNoiseWait_s, "NoiseWait");
    getStaticParam(&mParams.mNoiseCourbette_s, "NoiseCourbette");
    getStaticParam(&mParams.mNoiseDamage_s, "NoiseDamage");
    getStaticParam(&mParams.mNoiseMoveShift_s, "NoiseMoveShift");
    getStaticParam(&mParams.mNoiseMoveBack_s, "NoiseMoveBack");
    getStaticParam(&mParams.mNoiseGear1_s, "NoiseGear1");
    getStaticParam(&mParams.mNoiseGear2_s, "NoiseGear2");
    getStaticParam(&mParams.mNoiseGear3_s, "NoiseGear3");
    getStaticParam(&mParams.mNoiseGearTop_s, "NoiseGearTop");
}

}  // namespace uking::behavior
