#include "Game/AI/Action/actionGolemThrowPartsToTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

GolemThrowPartsToTarget::GolemThrowPartsToTarget(const InitArg& arg)
    : GolemThrowPartsToTargetBase(arg) {}

GolemThrowPartsToTarget::~GolemThrowPartsToTarget() = default;

bool GolemThrowPartsToTarget::init_(sead::Heap* heap) {
    return GolemThrowPartsToTargetBase::init_(heap);
}

void GolemThrowPartsToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemThrowPartsToTargetBase::enter_(params);
}

void GolemThrowPartsToTarget::leave_() {
    GolemThrowPartsToTargetBase::leave_();
}

void GolemThrowPartsToTarget::loadParams_() {
    GolemThrowPartsToTargetBase::loadParams_();
    getStaticParam(&mShootPitchMin_s, "ShootPitchMin");
    getStaticParam(&mShootPitchMax_s, "ShootPitchMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GolemThrowPartsToTarget::calc_() {
    GolemThrowPartsToTargetBase::calc_();
}

// NON_MATCHING: the unused front-vector length is removed; temporary stack slots differ.
void GolemThrowPartsToTarget::m32(sead::Vector3f* linear_velocity,
                                 sead::Vector3f* angular_velocity, sead::Matrix34f* mtx,
                                 ksys::phys::RigidBody* body) {
    if (!linear_velocity || !angular_velocity || !mtx)
        return;

    if (!body) {
        linear_velocity->set(0.0f, 0.0f, 0.0f);
        angular_velocity->set(0.0f, 0.0f, 0.0f);
        *mtx = mActor->getMtx();
        return;
    }

    body->getTransform(mtx);
    *angular_velocity = body->getAngularVelocity() * (1.0f / 30.0f);
    auto direction = body->getLinearVelocity() * (1.0f / 30.0f);
    const f32 speed = direction.normalize();
    // The original evaluates this length even though its result is discarded.
    const auto& actor_matrix = mActor->getMtx();
    const sead::Vector3f front{actor_matrix(0, 2), actor_matrix(1, 2), actor_matrix(2, 2)};
    front.length();
    const sead::Vector3f min_angle{*mShootPitchMin_s, -sead::Mathf::pi() / 2.0f, 0.0f};
    const sead::Vector3f max_angle{*mShootPitchMax_s, sead::Mathf::pi() / 2.0f, 0.0f};
    sead::Vector3f center;
    body->getCenterOfMassInWorld(&center);
    const auto* target = mTargetPos_d;
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sub_71005DDF80(linear_velocity, target, &center, &direction, &min_angle, &max_angle,
                   speed, gravity.y * (1.0f / 900.0f), 0.1f);
    if (linear_velocity->isNan()) {
        mActor->nullsub_4649();
        linear_velocity->set(0.0f, 0.0f, 0.0f);
    }
}

}  // namespace uking::action
