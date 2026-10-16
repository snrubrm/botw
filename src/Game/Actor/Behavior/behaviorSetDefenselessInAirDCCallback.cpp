#include "Game/Actor/Behavior/behaviorSetDefenselessInAirDCCallback.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

SetDefenselessInAirDCCallback::SetDefenselessInAirDCCallback(const InitArg& arg)
    : SetDefenselessDCCallback(arg) {}

SetDefenselessInAirDCCallback::~SetDefenselessInAirDCCallback() = default;

void SetDefenselessInAirDCCallback::calc() {
    SetDefenselessDCCallback::calc();
    auto* actor = mActor;
    if (!actor)
        return;
    if (isBgGroundHit(actor, false))
        sub_71005DA114(actor, m14());
    else
        setDamageCallbackTiming(actor, *mTiming_s, m14());
}

}  // namespace uking::behavior
