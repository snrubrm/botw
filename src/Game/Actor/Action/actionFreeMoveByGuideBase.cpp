#include "Game/Actor/Action/actionFreeMoveByGuideBase.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "Game/Actor/actRemains.h"
#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

void sub_710016C144(sead::Vector3f* value, const sead::Vector3f& target, f32 ratio,
                   f32 max_delta) {
    const f32 factor = ksys::VFR::getLerpFactor(ratio);
    max_delta *= ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f delta = target - *value;
    if (factor * delta.length() > max_delta) {
        const f32 length = delta.length();
        if (length > 0.0f)
            delta *= max_delta / length;
    } else {
        delta *= factor;
    }
    *value += delta;
}

// NON_MATCHING: rail rotation temporaries, quaternion and slerp scheduling.
bool FreeMoveByGuideBase::sub_710016BBC4() {
    auto* body = mActor->getMainBody();
    if (!body || !*mIsTraceRailPointRotation_s || mActor->getProfile() != "Remains")
        return false;
    auto* remains = sead::DynamicCast<act::Remains>(mActor);
    if (!remains || !remains->_b90 || !remains->_b90->_8.rail)
        return false;
    auto* rail = remains->_b90->_8.rail;
    f32 progress = remains->_b90->_30.progress;
    const s32 current = s32(progress);
    s32 next = s32(progress + 1.0f);
    if (next >= rail->getNumPoints()) {
        if (rail->isClosed()) {
            next = 0;
        } else {
            progress = static_cast<f32>(current);
            next = current;
        }
    }
    const sead::Vector3f first = rail->getPoint(current)->getRotate();
    const sead::Vector3f second = rail->getPoint(next)->getRotate();
    sead::Matrix34f first_rotation, second_rotation, rail_rotation;
    first_rotation.makeR(first);
    second_rotation.makeR(second);
    sead::Matrix34CalcCommon<f32>::slerpTo(
        rail_rotation, first_rotation, second_rotation,
        progress - static_cast<f32>(s32(progress)));
    sead::Quatf alignment;
    alignment.makeVectorRotation(rail_rotation.getBase(2), *mTargetFrontDir_d);
    sead::Quatf rotation;
    rail_rotation.toQuat(rotation);
    rotation = alignment * rotation;
    sead::Matrix34f target_rotation, transform;
    target_rotation.fromQuat(rotation);
    sead::Matrix34CalcCommon<f32>::slerpTo(
        transform, mActor->getMtx(), target_rotation, *mAngleAccRatio_s);
    transform.setTranslation(*mTargetPos_d);
    body->changePositionAndRotation(transform, sead::Mathf::epsilon());
    return true;
}

FreeMoveByGuideBase::FreeMoveByGuideBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMoveByGuideBase::~FreeMoveByGuideBase() = default;

bool FreeMoveByGuideBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMoveByGuideBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getMainBody())
        return;
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), false, 0, 0, -1.0f);
    _a8.value = 0;
    _a8.prev_value = 0;
    sub_7100741034(&_84, mActor);
    sub_7100741038(&_84, mActor);
}

void FreeMoveByGuideBase::leave_() {
    ksys::act::ai::Action::leave_();
}

bool FreeMoveByGuideBase::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Action::reenter_(other, true))
        return false;
    auto* prev = sead::DynamicCast<FreeMoveByGuideBase>(other);
    if (!prev)
        return false;
    _78 = prev->_78;
    _84 = prev->_84;
    _a8 = prev->_a8;
    _b4 = prev->_b4;
    return true;
}

void FreeMoveByGuideBase::loadParams_() {
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getStaticParam(&mMaxAngleAcc_s, "MaxAngleAcc");
    getStaticParam(&mAngleAccRatio_s, "AngleAccRatio");
    getStaticParam(&mKeepPlacementRotation_s, "KeepPlacementRotation");
    getStaticParam(&mIsTraceRailPointRotation_s, "IsTraceRailPointRotation");
    getStaticParam(&mKeepRotationBaseBoneName_s, "KeepRotationBaseBoneName");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetFrontDir_d, "TargetFrontDir");
}

// NON_MATCHING: retained native vector calculations and rotation scheduling.
void FreeMoveByGuideBase::calc_() {
    auto* body = mActor->getMainBody();
    if (!body) {
        setFailed();
        return;
    }
    if (sub_710016BBC4())
        return;
    const sead::Vector3f displacement = *mTargetPos_d - mActor->getMtx().getTranslation();
    const sead::Vector3f up(-0.0f, 1.0f, -0.0f);
    sead::Vector3f direction = displacement;
    ksys::util::sub_71011EFA00(&direction, direction, up);
    direction.normalize();
    displacement.length();
    body->changePosition(*mTargetPos_d, ksys::phys::KeepAngularVelocity{false},
                         sead::Mathf::epsilon());
    sub_7100741038(&_84, mActor);
    _a8.lerp(*mRotateAngleMax_s, 0.16f, *mRotateAngleMax_s / 10.0f);
    _a8.updateStats();
    sub_7100741578(&_84, *mTargetFrontDir_d, up, true, 0.16f, _a8.value, _a8.value / 10.0f);
    sead::Vector3f angular_velocity = body->getAngularVelocity();
    sub_7100741A7C(_84, body);
    const sead::Vector3f target_velocity = body->getAngularVelocity();
    sub_710016C144(&angular_velocity, target_velocity, *mAngleAccRatio_s, *mMaxAngleAcc_s);
    body->setAngularVelocity(angular_velocity, sead::Mathf::epsilon());
}

}  // namespace uking::action
