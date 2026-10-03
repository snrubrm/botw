#include "Game/AI/Action/actionThrownDown.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"

namespace uking::action {

ThrownDown::ThrownDown(const InitArg& arg) : Ragdoll(arg) {}

ThrownDown::~ThrownDown() = default;

bool ThrownDown::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void ThrownDown::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
}

void ThrownDown::leave_() {
    Ragdoll::leave_();
}

void ThrownDown::loadParams_() {
    Ragdoll::loadParams_();
    getDynamicParam(&mSetupSpeed_d, "SetupSpeed");
}

void ThrownDown::calc_() {
    Ragdoll::calc_();
}

void ThrownDown::m38() {
    sub_7100227134();
    auto* ragdoll = mActor->getRagdollInstance();
    if (!ragdoll)
        return;
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    if (actor->_868)
        actor->_868->sub_71006ED484();
    const int num_bodies = ragdoll->getRigidBodies_().size();
    sead::Vector3f linear_velocity = *mSetupSpeed_d;
    const sead::Vector3f angular_velocity = actor->getAngVelocity() * 30.0f;
    linear_velocity.y = 0.0f;
    ragdoll->getRigidBodies_().front()->setAngularVelocity(angular_velocity);
    for (int i = 0; i < num_bodies; ++i)
        ragdoll->getRigidBodies_()[i]->setLinearVelocity(linear_velocity);
}

}  // namespace uking::action
