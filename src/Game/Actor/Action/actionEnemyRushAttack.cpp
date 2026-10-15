#include "Game/Actor/Action/actionEnemyRushAttack.h"
#include <limits>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

EnemyRushAttack::EnemyRushAttack(const InitArg& arg) : RandomMoveAction(arg) {}

EnemyRushAttack::~EnemyRushAttack() = default;

bool EnemyRushAttack::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

// NON_MATCHING: vector stores and existing navmesh atomic setter instructions differ.
void EnemyRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
    auto* controller = mActor->getCharacterController();
    auto* nav = mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }
    _a0 = mActor->getMtx().getTranslation();
    _ac = _a0;
    _b8 = *mTargetPos_d;
    _c4 = true;
    _cc.reset(30.0f);
    if (!sub_710010BF08(true)) {
        setFailed();
        return;
    }
    if (nav) {
        _c8 = nav->_8->_a0->_24;
        nav->inlineSetField2BC(*mSpeed_s * 30.0f);
        nav->inlineSetField2C0(nav->_8->_6c * 1.5f);
        const f32 speed = _c8 * 2.0f;
        nav->_8->_a0->_24 = sead::Mathf::abs(speed) > std::numeric_limits<f32>::max() ?
                                ksys::phys::sUnk_7101ec27f4 : speed;
        nav->sub_7100F7604C(*mGoalDistanceTolerance_s);
    }
    playAS(mASKeyName_s.cstr(), false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_78);
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

// NON_MATCHING: saved actor-position component loads are reordered.
void EnemyRushAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    auto* nav = mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }
    if (!nav) {
        controller->sub_7100F5E7F0(0.0f);
        return;
    }
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    const f32 distance = (*mTargetPos_d - position).length();
    if (distance < 25.0f) {
        const f32 speed = sead::Mathf::clampMax(((25.0f - distance) / 12.5f + 2.0f) * _c8,
                                              _c8 * 4.0f);
        nav->_8->_a0->_24 = sead::Mathf::abs(speed) > std::numeric_limits<f32>::max() ?
                                ksys::phys::sUnk_7101ec27f4 : speed;
    }
    if (nav->_18) {
        RandomMoveAction::calc_();
        controller->sub_7100F5FDF0(controller->get64());
    }
    if (hasAttackInfo(mActor)) {
        setFinished();
        return;
    }
    if (!ksys::util::isVectorInvalid(nav->_194) &&
        (nav->_194 - position).length() < *mGoalDistanceTolerance_s * 3.0f) {
        _cc.update();
        if (_cc.value <= sead::Mathf::epsilon())
            setFailed();
    }
}

// NON_MATCHING: prediction, normalization and ray endpoint stores are reordered.
bool EnemyRushAttack::sub_710010BF08(bool update) {
    if (!_c4 && !update)
        return false;
    _a0 = mActor->getMtx().getTranslation();
    const sead::Vector3f target = *mTargetPos_d;
    const f32 prediction_rate = *mMovePredictionRate_s;
    const sead::Vector3f prediction = (target - _b8) * prediction_rate;
    const sead::Vector2f horizontal{target.x + prediction.x - _a0.x,
                                  target.z + prediction.z - _a0.z};
    const f32 distance = horizontal.length();
    sead::Vector3f direction{horizontal.x, 0.0f, horizontal.y};
    direction.normalize();
    if (distance < *mDisableUpdateTargetRadius_s) {
        _c4 = false;
    } else {
        const sead::Vector3f predicted = *mTargetPos_d + prediction;
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.setGroundHit(ksys::phys::GroundHit::HitAll);
        query.enableLayer(ksys::phys::ContactLayer::EntityNPC);
        query.enableLayer(ksys::phys::ContactLayer::EntityObject);
        query.enableLayer(ksys::phys::ContactLayer::EntityGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        query.setStart(_a0 + sead::Vector3f{0.0f, 1.0f, 0.0f});
        query.setEnd(predicted + sead::Vector3f{0.0f, 1.0f, 0.0f});
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
            _c4 = false;
    }
    if (!_c4 && !update)
        return false;
    return sub_710010C538(direction, distance + *mDisableUpdateTargetRadius_s * 0.75f *
                                                  mActor->getScale().x, 0.0f);
}

// NON_MATCHING: yaw rotation arithmetic and candidate-position stores are reordered.
bool EnemyRushAttack::sub_710010C538(const sead::Vector3f& direction, f32 distance,
                                    f32 angle_range) {
    const f32 angle = sead::GlobalRandom::instance()->getF32Range(-angle_range, angle_range);
    sead::Matrix33f rotation;
    rotation.makeR({0.0f, angle, 0.0f});
    sead::Vector3f rotated;
    rotated.setRotated(rotation, direction);
    const sead::Vector3f target = _a0 + rotated * distance;
    auto* havok_ai = ksys::phys::HavokAI::instance();
    if (!havok_ai || !havok_ai->sub_7100F86174(_a0, target, nullptr, 10.0f))
        return false;
    _ac = target;
    _b8 = *mTargetPos_d;
    return true;
}

}  // namespace uking::action
