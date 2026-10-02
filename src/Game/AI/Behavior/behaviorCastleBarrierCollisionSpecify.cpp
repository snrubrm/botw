#include "Game/AI/Behavior/behaviorCastleBarrierCollisionSpecify.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

CastleBarrierCollisionSpecify::CastleBarrierCollisionSpecify(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

bool CastleBarrierCollisionSpecify::m6(sead::Heap* heap) {
    _28.setFunction(&CastleBarrierCollisionSpecify::sub_710061BCB0);
    return true;
}

void CastleBarrierCollisionSpecify::m8() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor))
        wall->sub_7100E245B8(&_28);
}

void CastleBarrierCollisionSpecify::m9() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor))
        wall->sub_7100E245B8(nullptr);
}

void CastleBarrierCollisionSpecify::sub_710061BCB0(ksys::phys::RigidBody* body) {
    body->setGroundHitMask(body->getContactLayer(), 0);
}

}  // namespace uking::behavior
