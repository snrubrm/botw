#include "Game/Actor/Action/actionFreeMoveToTargetInWataer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

FreeMoveToTargetInWataer::FreeMoveToTargetInWataer(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToTargetInWataer::~FreeMoveToTargetInWataer() = default;

bool FreeMoveToTargetInWataer::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToTargetInWataer::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (*mForceUseFrontDir_s) {
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        controller->sub_7100F5EDBC(front);
    }
    mActor->getMtx().getBase(_f8, 2);
}

void FreeMoveToTargetInWataer::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToTargetInWataer::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mAllowMoveWaterDepth_s, "AllowMoveWaterDepth");
    getStaticParam(&mForceTurnLimitSpeedStream_s, "ForceTurnLimitSpeedStream");
    getStaticParam(&mIsForceTurnAgainstStream_s, "IsForceTurnAgainstStream");
    getStaticParam(&mForceUseFrontDir_s, "ForceUseFrontDir");
}

void FreeMoveToTargetInWataer::calc_() {
    FreeMoveToTarget::calc_();
}

// NON_MATCHING: position component loads and direction stores.
bool FreeMoveToTargetInWataer::m32(ksys::phys::CharacterController* controller) {
    if (!mActor->get68f()) {
        _28 = controller->get64() + sead::Vector3f{0.0f, 0.5f, 0.0f};
        _28.normalize();
        _cc = mActor->getMtx().getTranslation();
        sub_710016B114(controller->sub_7100F5EF00());
        return false;
    }
    m38();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    const f32 water_depth = mActor->get68f() ? mActor->get6f0() - position.y : 0.0f;
    const f32 allowed_depth = *mAllowMoveWaterDepth_s;
    if (water_depth + (position.y - _cc.y) < allowed_depth)
        _cc.y = position.y + water_depth - sead::Mathf::clampMin(allowed_depth, 0.0f);
    _28 = _cc - position;
    const f32 distance = _28.normalize();
    if (distance <= *mFinishRadius_s) {
        if (*mForceUseFrontDir_s) {
            if (_f8.isNan() || (_f8.x == 0.0f && _f8.y == 0.0f && _f8.z == 0.0f))
                mActor->getMtx().getBase(_f8, 2);
            _28 = _f8;
        } else {
            _28 = controller->get64();
        }
    }
    if (_28.isNan() || (_28.x == 0.0f && _28.y == 0.0f && _28.z == 0.0f)) {
        sead::FixedSafeString<256> name;
        // The original fills this diagnostic name and discards it.
        mActor->getRootAi()->getCurrentName(&name, this);
    }
    sub_710016B114(controller->sub_7100F5EF00());
    return true;
}

// NON_MATCHING: forward direction component stores are paired differently.
void FreeMoveToTargetInWataer::m33(ksys::phys::CharacterController* controller) {
    _44 = *mTargetPos_d;
    _50 = _cc;
    FreeMove::m33(controller);
    sead::Vector3f front = controller->get64();
    sead::Vector3f stream = controller->get180();
    const f32 speed = stream.normalize();
    auto* actor = mActor;
    if (actor->get68f() &&
        actor->get6f0() - actor->getMtx().getTranslation().y >= *mAllowMoveWaterDepth_s &&
        *mIsForceTurnAgainstStream_s && speed > *mForceTurnLimitSpeedStream_s) {
        actor->getMtx().getBase(_f8, 2);
        sead::Vector3f against_stream = -stream;
        ksys::util::sub_71011EE70C(&against_stream, &front, 0.25f, sead::Mathf::deg2rad(15.0f),
                                  sead::Mathf::deg2rad(0.1f));
        ksys::util::sub_71011EE70C(&_f8, &against_stream, 0.16f, *mParams.mAngleSpeed_s * 0.4f,
                                  sead::Mathf::deg2rad(0.1f));
        _f8.normalize();
        controller->sub_7100F5FDF0(_f8);
    } else {
        sead::Vector3f previous = _f8;
        actor->getMtx().getBase(_f8, 2);
        ksys::util::sub_71011EE70C(&_f8, &previous, 0.4f, *mParams.mAngleSpeed_s,
                                  sead::Mathf::deg2rad(0.1f));
    }
}

bool FreeMoveToTargetInWataer::m34() {
    const sead::Vector3f diff = _cc - mActor->getMtx().getTranslation();
    return diff.squaredLength() < *mFinishRadius_s * *mFinishRadius_s;
}

void FreeMoveToTargetInWataer::m38() {
    _cc = *mTargetPos_d;
}

}  // namespace uking::action
