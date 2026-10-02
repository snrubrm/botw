#include "Game/AI/Behavior/behaviorSetDefenselessInAirDCCallback.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

SetDefenselessInAirDCCallback::SetDefenselessInAirDCCallback(const InitArg& arg)
    : SetDefenselessDCCallback(arg) {}

SetDefenselessInAirDCCallback::~SetDefenselessInAirDCCallback() = default;

void SetDefenselessInAirDCCallback::m7() {
    SetDefenselessDCCallback::m7();
    auto* actor = mActor;
    if (!actor)
        return;
    if (isBgGroundHit(actor, false))
        sub_71005DA114(actor, m14());
    else
        setDamageCallbackTiming(actor, *mTiming_s, m14());
}

}  // namespace uking::behavior
