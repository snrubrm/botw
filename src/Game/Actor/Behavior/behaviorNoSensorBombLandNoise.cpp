#include "Game/Actor/Behavior/behaviorNoSensorBombLandNoise.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

NoSensorBombLandNoise::NoSensorBombLandNoise(const InitArg& arg) : NoiseBase(arg) {}

NoSensorBombLandNoise::~NoSensorBombLandNoise() = default;

bool NoSensorBombLandNoise::init_(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: `!_60` / the `_61` test compile differently (the original treats _61 as a byte) and
// the velocity loads are scheduled differently
void NoSensorBombLandNoise::calc() {
    const bool landed = isBgGroundHit(mActor, false) || isLandedMaybe(mActor, false);
    _61 = landed && !_60;
    if (_58 > 0.0f)
        ksys::Timer::update(&_58, -1.0f);
    else if (_61)
        sub_710062E9F8();
    else if (landed && mActor->getVelocity().length() > *mNoiseSpeed_s)
        sub_710062E9F8();
    else
        sub_710062E9F0();
    NoiseBase::calc();
    _60 = landed;
}

void NoSensorBombLandNoise::enter() {
    sub_710062E9F0();
    const int no_noise_frame = *mNoNoiseFrame_s;
    _61 = false;
    _58 = no_noise_frame;
}

void NoSensorBombLandNoise::leave() {
    NoiseBase::leave();
}

void NoSensorBombLandNoise::loadParams() {
    NoiseBase::loadParams();
    getStaticParam(&mNoNoiseFrame_s, "NoNoiseFrame");
    getStaticParam(&mLandNoiseValue_s, "LandNoiseValue");
    getStaticParam(&mNoiseSpeed_s, "NoiseSpeed");
}

// NON_MATCHING: csel operand order
f32 NoSensorBombLandNoise::m14() {
    if (_61)
        return *mNoiseValue_s;
    return *mLandNoiseValue_s;
}

}  // namespace uking::behavior
