#include "Game/AI/Behavior/behaviorPlayerLandNoiseBase.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

PlayerLandNoiseBase::PlayerLandNoiseBase(const InitArg& arg) : Noise(arg) {}

void PlayerLandNoiseBase::m7() {
    Noise::m7();
    const bool landed = isBgGroundHit(mActor, false) || isLandedMaybe(mActor, false);
    if (landed && !_100)
        sub_710062E9F8();
    else
        sub_710062E9F0();
    _100 = landed;
}

void PlayerLandNoiseBase::m8() {
    Noise::m8();
    _100 = false;
}

}  // namespace uking::behavior
