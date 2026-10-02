#include "Game/AI/Behavior/behaviorHorseAttackBehavior.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

HorseAttackBehavior::HorseAttackBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseAttackBehavior::~HorseAttackBehavior() = default;

bool HorseAttackBehavior::m6(sead::Heap* heap) {
    return true;
}

void HorseAttackBehavior::m8() {
    _128 = 0;
}

void HorseAttackBehavior::m9() {
    _b8.remove();
    _48.remove();
    _80.remove();
    _f0.remove();
    auto* body_set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC());
    if (!body_set)
        return;
    if (*mIsRemovedAllAtkCollision_s) {
        body_set->removeFromWorld();
        return;
    }
    if (auto* body = body_set->findBodyByHavokName(mAtkCollisionName_s))
        body->removeFromWorld();
}

void HorseAttackBehavior::loadParams() {
    getStaticParam(&mChargeAttackOffsetY_s, "ChargeAttackOffsetY");
    getStaticParam(&mIsRemovedAllAtkCollision_s, "IsRemovedAllAtkCollision");
    getStaticParam(&mAtkCollisionName_s, "AtkCollisionName");
}

}  // namespace uking::behavior
