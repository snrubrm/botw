#include "Game/Actor/Action/actionEitherSideExplode.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EitherSideExplode::EitherSideExplode(const InitArg& arg) : Explode(arg) {}

EitherSideExplode::~EitherSideExplode() = default;

bool EitherSideExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void EitherSideExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void EitherSideExplode::leave_() {
    Explode::leave_();
}

void EitherSideExplode::loadParams_() {
    Explode::loadParams_();
    getDynamicParam(&mIsPlayerAttack_d, "IsPlayerAttack");
}

void EitherSideExplode::calc_() {
    Explode::calc_();
}

ksys::phys::SphereRigidBody* EitherSideExplode::m32() {
    auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC());
    if (!set)
        return nullptr;
    if (*mIsPlayerAttack_d)
        return sead::DynamicCast<ksys::phys::SphereRigidBody>(
            set->findBodyByHavokName("AtkPlayerExplode"));
    return sead::DynamicCast<ksys::phys::SphereRigidBody>(
        set->findBodyByHavokName("AtkEnemyExplode"));
}

}  // namespace uking::action
