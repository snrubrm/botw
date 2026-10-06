#include "Game/AI/Action/actionEnemyRigidBodyDieBase.h"
#include "math/seadBoundBox.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EnemyRigidBodyDieBase::EnemyRigidBodyDieBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyRigidBodyDieBase::~EnemyRigidBodyDieBase() = default;

bool EnemyRigidBodyDieBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyRigidBodyDieBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
