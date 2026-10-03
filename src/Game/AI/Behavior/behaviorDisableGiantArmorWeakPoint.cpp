#include "Game/AI/Behavior/behaviorDisableGiantArmorWeakPoint.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

DisableGiantArmorWeakPoint::DisableGiantArmorWeakPoint(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

DisableGiantArmorWeakPoint::~DisableGiantArmorWeakPoint() = default;

bool DisableGiantArmorWeakPoint::m6(sead::Heap* heap) {
    return true;
}

void DisableGiantArmorWeakPoint::m7() {}

void DisableGiantArmorWeakPoint::m8() {
    const auto& name = sub_710072D53C(mActor, *mWeakPointIdx_s);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), name.cstr()))
        body->removeFromWorld();
}

void DisableGiantArmorWeakPoint::m9() {
    const auto& name = sub_710072D53C(mActor, *mWeakPointIdx_s);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), name.cstr()))
        body->addToWorld();
}

void DisableGiantArmorWeakPoint::loadParams() {
    getStaticParam(&mWeakPointIdx_s, "WeakPointIdx");
}

}  // namespace uking::behavior
