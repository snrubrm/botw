#include "Game/AI/Action/actionStalEnemyDie.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

StalEnemyDie::StalEnemyDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalEnemyDie::~StalEnemyDie() = default;

bool StalEnemyDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StalEnemyDie::sub_7100276D2C() {
    auto* actor = mActor;
    _90 = false;
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F60AE0();
        controller->sub_7100F62CA8(false);
        controller->sub_7100F605F0();
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    }
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        if (dynamic_actor->_868)
            dynamic_actor->_868->sub_71006ED484();
    }
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBDB90(physics->get112(), 1.0f);
    if (auto* ragdoll = actor->getRagdollInstance()) {
        const int num_bodies = ragdoll->getRigidBodies_().size();
        sead::Vector3f linear_velocity = actor->getVelocity() * 30.0f;
        const sead::Vector3f angular_velocity = actor->getAngVelocity() * 30.0f;
        ragdoll->getRigidBodies_().front()->setAngularVelocity(angular_velocity);
        linear_velocity *= 0.6f;
        for (int i = 0; i < num_bodies; ++i)
            ragdoll->getRigidBodies_()[i]->setLinearVelocity(linear_velocity);
    }
    _84.reset(*mTime_s);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _80 = false;
}

void StalEnemyDie::enter_(ksys::act::ai::InlineParamPack* params) {
    _90 = true;
    if (mPreDieASName_s.isEmpty())
        sub_7100276D2C();
    else
        playAS(mPreDieASName_s.cstr(), false, 0, 0, -1.0f);
    auto* actor = mActor;
    if (auto* life = actor->getLife())
        *life = 0;
    sub_7100728B38(actor);
    sub_710072BB28(actor);
}

void StalEnemyDie::leave_() {
    auto* actor = mActor;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor))
        dynamic_actor->sub_71006DD92C(false);
    ksys::act::enableAllAttClients(actor);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
        controller->sub_7100F62CA8(true);
        controller->sub_7100F60604();
    }
    if (auto* physics = actor->getPhysics()) {
        physics->sub_7100FBDB90(physics->get112(), 0.0f);
        if (auto* ragdoll = physics->getRagdollInstance()) {
            const int num = ragdoll->getNumConstraints();
            for (int i = 0; i < num; ++i)
                ragdoll->enableConstraint(i, true);
        }
    }
    sub_71007A3800(actor);
}

void StalEnemyDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mForceDropWeapon_s, "ForceDropWeapon");
    getStaticParam(&mPreDieASName_s, "PreDieASName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollName_s, "PosBaseRagdollName");
    getStaticParam(&mEnableConstraintName_s, "EnableConstraintName");
}

void StalEnemyDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
