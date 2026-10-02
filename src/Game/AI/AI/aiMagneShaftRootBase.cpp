#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

MagneShaftRootBase::MagneShaftRootBase(const InitArg& arg) : MagneStickRoot(arg) {}

MagneShaftRootBase::~MagneShaftRootBase() = default;

bool MagneShaftRootBase::init_(sead::Heap* heap) {
    return MagneStickRoot::init_(heap);
}

void MagneShaftRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneStickRoot::enter_(params);
}

void MagneShaftRootBase::calc_() {
    MagneStickRoot::calc_();
}

void MagneShaftRootBase::leave_() {
    MagneStickRoot::leave_();
}

void MagneShaftRootBase::loadParams_() {
    MagneStickRoot::loadParams_();
}

bool MagneShaftRootBase::m41(const sead::Matrix34f* mtx, const sead::Vector3f* a,
                             const sead::Vector3f* b) {
    auto* actor = mActor;
    if (!actor)
        return false;

    sead::Vector3f dir = actor->getMtx().getTranslation() - *b;
    dir.normalize();
    sead::Vector3f axis{mtx->m[0][2], mtx->m[1][2], mtx->m[2][2]};
    axis.normalize();
    return std::acos(sead::Mathf::abs(dir.dot(axis))) <= sead::Mathf::deg2rad(4);
}

void MagneShaftRootBase::m48(f32 radius, const sead::Matrix34f* mtx, const sead::Vector3f* a,
                             const sead::Vector3f* b) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* body = actor->getMainBody();
    if (!body)
        return;

    const f32 distance = (sead::Vector3f::ez * a->z - *a).length();
    body->changeMotionType(ksys::phys::MotionType::Dynamic);
    if (distance < radius) {
        body->setMaxLinearVelocity(_80 * 0.1f);
        body->setMaxAngularVelocity(_84 * 0.1f);
        sead::Vector3f position;
        m49(&position, {mtx->m[0][3], mtx->m[1][3], mtx->m[2][3]}, *b);
        body->changePosition(position, ksys::phys::KeepAngularVelocity{false});
        m50();
    } else {
        body->setMaxLinearVelocity(_80);
        body->setMaxAngularVelocity(_84);
    }
}

void MagneShaftRootBase::m50() {
    if (mActor) {
        if (auto* body = m52())
            body->enableGroundCollision(false);
    }
}

void MagneShaftRootBase::m51() {
    if (mActor) {
        if (auto* body = m52())
            body->enableGroundCollision(true);
    }
}

}  // namespace uking::ai
