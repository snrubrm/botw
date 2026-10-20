#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include <cmath>
#include <limits>

Unk_71024f7180::Unk_71024f7180() = default;

Unk_71024f7180::~Unk_71024f7180() = default;

void Unk_71024f7180::m5() {
    sead::Matrix34f transform;
    mBodyA->getTransform(&transform);
    sead::Matrix34f result;
    result.setMul(transform, mTransform);
    mBodyB->setTransform(result, ksys::phys::PropagateToLinkedMotions{true});
}

bool Unk_71024f7180::m6() {
    return _9c;
}

// NON_MATCHING: frame-vector initialization and inverse rotation calculations differ in scheduling.
bool Unk_71024f7180::init(const InitArg& arg, sead::Heap* heap) {
    ksys::phys::LimitHingeCs::Param param;
    const Unk_7102519e58::InitArg base_arg{arg.instance, arg.body_a, arg.body_b};
    if (!sub_71012AD3CC(param, &mTransform, base_arg, heap))
        return false;
    param.body_a = mBodyA;
    param.body_b = mBodyB;
    param._24 = mTransform.getTranslation();
    param._30 = sead::Vector3f::zero;
    param._3c = arg.axis;
    sead::Matrix33f inverse_rotation(mTransform);
    inverse_rotation.transpose();
    param._48.setRotated(inverse_rotation, param._3c);
    param._48.normalize();
    param._54 = arg.perpendicular;
    param._60.setRotated(inverse_rotation, param._54);
    param._60.normalize();
    param._6c = 0.0f;
    param._70 = 0.0f;
    param._74 = 5000.0f;
    mConstraint = ksys::phys::LimitHingeCs::make(param, heap);
    _48 = param._48;
    _54 = param._60;
    _60 = param._54;
    return mConstraint != nullptr;
}

// NON_MATCHING: relative-frame calculations and tolerance branches differ in scheduling.
void Unk_71024f7180::m4(const sead::Matrix34f& matrix) {
    auto* hinge = sead::DynamicCast<ksys::phys::LimitHingeCs>(mConstraint);
    if (!hinge)
        return;
    f32 tau = hinge->sub_7100F6E358() + 0.1f;
    if (tau > 1.0f)
        tau = 1.0f;
    hinge->sub_7100F6E334(tau);
    sead::Matrix34f transform_a;
    sead::Matrix34f transform_b;
    mBodyA->getTransform(&transform_a);
    mBodyB->getTransform(&transform_b);
    sead::Matrix34f inverse_a;
    inverse_a.setInverse(transform_a);
    sead::Matrix34f relative;
    relative.setMul(inverse_a, transform_b);
    sead::Vector3f target_axis;
    target_axis.setRotated(matrix, _54);
    sead::Vector3f current_axis;
    current_axis.setRotated(relative, _54);
    const sead::Vector3f axis_error = target_axis - current_axis;
    _9c = false;
    if (axis_error.x <= 0.03f && -0.03f <= axis_error.x &&
        axis_error.y <= 0.03f && -0.03f <= axis_error.y &&
        axis_error.z <= 0.03f && -0.03f <= axis_error.z) {
        sead::Vector3f expected_position;
        expected_position.setRotated(transform_a, mTransform.getTranslation());
        const sead::Vector3f position_error =
            expected_position - (transform_b.getTranslation() - transform_a.getTranslation());
        _9c = position_error.x <= 0.03f && -0.03f <= position_error.x &&
              position_error.y <= 0.03f && -0.03f <= position_error.y &&
              position_error.z <= 0.03f && -0.03f <= position_error.z;
    }
    const f32 angle = std::atan2(target_axis.cross(_60).length(), target_axis.dot(_60));
    if (hinge->sub_7100F6E340() != angle) {
        hinge->sub_7100F6E300(angle);
        mBodyA->setMotionFlag(ksys::phys::RigidBody::MotionFlag::_20000);
        mBodyB->setMotionFlag(ksys::phys::RigidBody::MotionFlag::_20000);
    }
    mBodyB->setAngularVelocity(mBodyA->getAngularVelocity(), std::numeric_limits<f32>::epsilon());
    mBodyB->setLinearVelocity(mBodyA->getLinearVelocity(), std::numeric_limits<f32>::epsilon());
}
