#include "Game/AI/Action/actionEnemyRushAttack.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

EnemyRushAttack::EnemyRushAttack(const InitArg& arg) : RandomMoveAction(arg) {}

EnemyRushAttack::~EnemyRushAttack() = default;

bool EnemyRushAttack::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void EnemyRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void EnemyRushAttack::leave_() {
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        if (auto* body = set->getRigidBodies()[0])
            body->setContactLayer(ksys::phys::ContactLayer::SensorNoHit);
    }
    sub_71005DA114(mActor, &_78);
    if (auto* nav = mActor->m45()) {
        const f32 value = _c8;
        nav->_8->_a0->_24 = sead::Mathf::abs(value) > std::numeric_limits<f32>::max() ?
                                ksys::phys::sUnk_7101ec27f4 :
                                value;
    }
    RandomMoveAction::leave_();
}

s32 EnemyRushAttack::m32(RandomMovePoints* points) {
    sub_710010BF08(false);
    points->add(_ac);
    return *mUpdateTargetPosInterval_s;
}

void EnemyRushAttack::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDisableUpdateTargetRadius_s, "DisableUpdateTargetRadius");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mMovePredictionRate_s, "MovePredictionRate");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyRushAttack::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
