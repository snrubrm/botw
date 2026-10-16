#include "Game/Actor/Behavior/behaviorPlayerLandNoiseBase.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

PlayerLandNoiseBase::PlayerLandNoiseBase(const InitArg& arg) : Noise(arg) {}

void PlayerLandNoiseBase::calc() {
    Noise::calc();
    const bool landed = isBgGroundHit(mActor, false) || isLandedMaybe(mActor, false);
    if (landed && !_100)
        sub_710062E9F8();
    else
        sub_710062E9F0();
    _100 = landed;
}

void PlayerLandNoiseBase::enter() {
    Noise::enter();
    _100 = false;
}

}  // namespace uking::behavior
