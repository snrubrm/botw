#include "Game/AI/Behavior/behaviorSpeedTerror.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

// NON_MATCHING: the original tail-calls memset for the parameters (known clang difference)
SpeedTerror::SpeedTerror(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool SpeedTerror::m6(sead::Heap* heap) {
    _28.sub_7100D78564(heap);
    return true;
}

void SpeedTerror::m9() {
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_28);
}

void SpeedTerror::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeedTh_s, "SpeedTh");
    getStaticParam(&mRemoveSpTh_s, "RemoveSpTh");
    getStaticParam(&mIsPlayerLayer_s, "IsPlayerLayer");
    getStaticParam(&mIsNpcLayer_s, "IsNpcLayer");
    getStaticParam(&mIsEnemyLayer_s, "IsEnemyLayer");
    getStaticParam(&mIsGuardianLayer_s, "IsGuardianLayer");
    getStaticParam(&mIsImpulseLayer_s, "IsImpulseLayer");
    getStaticParam(&mIsFireLayer_s, "IsFireLayer");
    getStaticParam(&mIsInsectLayer_s, "IsInsectLayer");
    getStaticParam(&mIsHorseLayer_s, "IsHorseLayer");
    getStaticParam(&mIsAnimalLayer_s, "IsAnimalLayer");
    getStaticParam(&mIsWolfLinkLayer_s, "IsWolfLinkLayer");
    getStaticParam(&mIsIceLayer_s, "IsIceLayer");
    getStaticParam(&mIsElectricLayer_s, "IsElectricLayer");
}

SpeedTerror::~SpeedTerror() {
    _28.sub_7100D786EC();
}

}  // namespace uking::behavior
