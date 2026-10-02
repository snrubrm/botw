#include "Game/AI/Action/actionCarriedNoHit.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

CarriedNoHit::CarriedNoHit(const InitArg& arg) : Carried(arg) {}

CarriedNoHit::~CarriedNoHit() = default;

void CarriedNoHit::enter_(ksys::act::ai::InlineParamPack* params) {
    Carried::enter_(params);
    if (auto* body = mActor->getMainBody())
        body->setContactLayerAndGroundHit(ksys::phys::ContactLayer::EntityNoHit, ksys::phys::GroundHit::HitAll);
    sub_71007A36BC(mActor);
}

void CarriedNoHit::leave_() {
    Carried::leave_();
    if (auto* body = mActor->getMainBody()) {
        if (auto* physics = mActor->getPhysics())
            physics->sub_7100FBAF18(body);
    }
    sub_71007A3540(mActor);
}

}  // namespace uking::action
