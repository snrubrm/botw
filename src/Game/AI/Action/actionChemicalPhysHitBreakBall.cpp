#include "Game/AI/Action/actionChemicalPhysHitBreakBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ChemicalPhysHitBreakBall::ChemicalPhysHitBreakBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

ChemicalPhysHitBreakBall::~ChemicalPhysHitBreakBall() = default;

bool ChemicalPhysHitBreakBall::m33() {
    auto* actor = mActor;
    if (!actor)
        return false;
    if (hasAttackInfo(actor) || isBgGroundHit(actor, false) || isLandedMaybe(actor, false))
        return true;
    if (actor->get68f())
        return true;
    return ChemicalPhysBall::m33();
}

}  // namespace uking::action
