#include "Game/AI/Behavior/behaviorNoSensorBombLandNoise.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

NoSensorBombLandNoise::NoSensorBombLandNoise(const InitArg& arg) : NoiseBase(arg) {}

NoSensorBombLandNoise::~NoSensorBombLandNoise() = default;

bool NoSensorBombLandNoise::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: `!_60` / the `_61` test compile differently (the original treats _61 as a byte) and
// the velocity loads are scheduled differently
void NoSensorBombLandNoise::m7() {
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
    NoiseBase::m7();
    _60 = landed;
}

// NON_MATCHING: the _61 store is scheduled before the parameter load
void NoSensorBombLandNoise::m8() {
    sub_710062E9F0();
    _61 = false;
    _58 = *mNoNoiseFrame_s;
}

void NoSensorBombLandNoise::m9() {
    NoiseBase::m9();
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
