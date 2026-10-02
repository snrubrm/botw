#include "Game/AI/Behavior/behaviorHorseAttackBehavior.h"

namespace uking::behavior {

HorseAttackBehavior::HorseAttackBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool HorseAttackBehavior::m6(sead::Heap* heap) {
    return true;
}

void HorseAttackBehavior::loadParams() {
    getStaticParam(&mChargeAttackOffsetY_s, "ChargeAttackOffsetY");
    getStaticParam(&mIsRemovedAllAtkCollision_s, "IsRemovedAllAtkCollision");
    getStaticParam(&mAtkCollisionName_s, "AtkCollisionName");
}

}  // namespace uking::behavior
