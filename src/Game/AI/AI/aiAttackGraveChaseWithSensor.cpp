#include "Game/AI/AI/aiAttackGraveChaseWithSensor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::ai {

AttackGraveChaseWithSensor::AttackGraveChaseWithSensor(const InitArg& arg)
    : AttackGraveChase(arg) {}

AttackGraveChaseWithSensor::~AttackGraveChaseWithSensor() = default;

bool AttackGraveChaseWithSensor::init_(sead::Heap* heap) {
    if (!AttackGraveChase::init_(heap))
        return false;
    return mActor->findPhysicsBodyByName(mRigidBodyGroupName_s.cstr(), mRigidBodyName_s.cstr()) !=
           nullptr;
}

void AttackGraveChaseWithSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackGraveChase::enter_(params);
    auto* body =
        mActor->findPhysicsBodyByName(mRigidBodyGroupName_s.cstr(), mRigidBodyName_s.cstr());
    if (!body) {
        setFailed();
        return;
    }
    if (!body->isAddedToWorld())
        body->addToWorld();
}

void AttackGraveChaseWithSensor::leave_() {
    AttackGraveChase::leave_();
}

void AttackGraveChaseWithSensor::loadParams_() {
    AttackGraveChase::loadParams_();
    getStaticParam(&mRigidBodyGroupName_s, "RigidBodyGroupName");
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void AttackGraveChaseWithSensor::calc_() {
    AttackGraveChase::calc_();
    auto* body =
        mActor->findPhysicsBodyByName(mRigidBodyGroupName_s.cstr(), mRigidBodyName_s.cstr());
    if (!body) {
        setFailed();
        return;
    }
    auto* info = body->getContactPointInfo();
    if (!info) {
        setFailed();
        return;
    }
    if (info->begin() != info->end())
        setFinished();
}

}  // namespace uking::ai
