#include "Game/Actor/Action/actionEnemyRigidBodyDieBase.h"
#include "math/seadBoundBox.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

EnemyRigidBodyDieBase::EnemyRigidBodyDieBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyRigidBodyDieBase::~EnemyRigidBodyDieBase() = default;

bool EnemyRigidBodyDieBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// Turns the enemy into a dynamic rigid body (the dying ragdoll-like body) with the velocities from m32.
void EnemyRigidBodyDieBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        setFailed();
        return;
    }
    auto* physics = enemy->getPhysics();
    if (!physics) {
        setFailed();
        return;
    }
    auto* body = enemy->getMainBody();
    if (!body) {
        setFailed();
        return;
    }

    if (auto* drop_data = sead::DynamicCast<ksys::act::DropData>(mActor->getDropData())) {
        drop_data->_c |= 0x80;
        if (auto* main_body = mActor->getMainBody()) {
            sead::BoundBox3f aabb;
            main_body->getAabbInWorld(&aabb);
            *mForceSetDropPos_a = aabb.getCenter();
        } else {
            mActor->getMtx().getTranslation(*mForceSetDropPos_a);
        }
    }
    enemy->_e84.set(0x800);
    if (auto* controller = enemy->getCharacterController()) {
        if (controller->sub_7100F5E954())
            controller->sub_7100F5EC44();
    }
    if (!body->isAddedToWorld())
        body->addToWorld();
    physics->setFlag2();
    body->setTransform(enemy->getMtx(), ksys::phys::PropagateToLinkedMotions{true});

    sead::Vector3f velocity = sead::Vector3f::zero;
    sead::Vector3f angular_velocity = sead::Vector3f::zero;
    m32(&velocity, &angular_velocity);
    body->setLinearVelocity(velocity, sead::Mathf::epsilon());
    body->setAngularVelocity(angular_velocity, sead::Mathf::epsilon());
    body->changeMotionType(ksys::phys::MotionType::Dynamic);
    body->setContactLayer(ksys::phys::ContactLayer::EntityNPC);
}

void EnemyRigidBodyDieBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyRigidBodyDieBase::loadParams_() {
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
}

void EnemyRigidBodyDieBase::calc_() {
    if (auto* body = mActor->getMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInWorld(&aabb);
        *mForceSetDropPos_a = aabb.getCenter();
    }
}

// NON_MATCHING: the original loads the three components of each vector before scaling and stores them
// separately (no stp pairs); a by-value local copy of the vectors fixes the loads but not the stores.
void EnemyRigidBodyDieBase::m32(sead::Vector3f* velocity, sead::Vector3f* angular_velocity) {
    const auto& v = mActor->getVelocity();
    velocity->x = v.x * 30.0f;
    velocity->y = v.y * 30.0f;
    velocity->z = v.z * 30.0f;
    const auto& w = mActor->getAngVelocity();
    angular_velocity->x = w.x * 30.0f;
    angular_velocity->y = w.y * 30.0f;
    angular_velocity->z = w.z * 30.0f;
}

}  // namespace uking::action
