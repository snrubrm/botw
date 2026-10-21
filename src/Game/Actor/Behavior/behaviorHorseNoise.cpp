#include "Game/Actor/Behavior/behaviorHorseNoise.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void HorseNoise::calc() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;

    f32 noise;
    switch (act::Rideable::Gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b)) {
    case act::Rideable::Gear::_0:
        noise = *mParams.mNoiseWait_s;
        break;
    case act::Rideable::Gear::_1:
        noise = *mParams.mNoiseGear1_s;
        break;
    case act::Rideable::Gear::_2:
        noise = *mParams.mNoiseGear2_s;
        break;
    case act::Rideable::Gear::_3:
        noise = *mParams.mNoiseGear3_s;
        break;
    case act::Rideable::Gear::_4:
        noise = *mParams.mNoiseGearTop_s;
        break;
    default:
        noise = 0.0f;
        break;
    }

    const auto& name = mActor->getASList()->x_1(0, 0);
    if (name == act::sUnk_7102603180 || name == act::sUnk_7102603190)
        noise = sead::Mathf::max(noise, *mParams.mNoiseCourbette_s);
    else if (name == act::sUnk_7102603220)
        noise = sead::Mathf::max(noise, *mParams.mNoiseDamage_s);
    else if (name == act::sUnk_7102603160)
        noise = sead::Mathf::max(noise, *mParams.mNoiseMoveShift_s);
    else if (name == act::sUnk_7102603150)
        noise = sead::Mathf::max(noise, *mParams.mNoiseMoveBack_s);

    sub_71005D8D4C(mActor, noise, 1, false);
}

}  // namespace uking::behavior
