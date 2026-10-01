#include "Game/AI/Action/actionReboundHit.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ReboundHit::ReboundHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ReboundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Vector3f dir;
    body->getTransform().getBase(dir, 2);
    body->setLinearVelocity(dir * *mSpeed_s * 30.0f);
    body->setGravityFactor(*mGravityRate_s);
}

void ReboundHit::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mGravityRate_s, "GravityRate");
}

}  // namespace uking::action
