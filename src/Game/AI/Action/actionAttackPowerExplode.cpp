#include "Game/AI/Action/actionAttackPowerExplode.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AttackPowerExplode::AttackPowerExplode(const InitArg& arg) : Explode(arg) {}

AttackPowerExplode::~AttackPowerExplode() = default;

bool AttackPowerExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void AttackPowerExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void AttackPowerExplode::leave_() {
    Explode::leave_();
}

void AttackPowerExplode::loadParams_() {
    Explode::loadParams_();
    getDynamicParam(&mIsPlayerAttack_d, "IsPlayerAttack");
}

void AttackPowerExplode::calc_() {
    Explode::calc_();
}

ksys::phys::SphereRigidBody* AttackPowerExplode::m32() {
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
