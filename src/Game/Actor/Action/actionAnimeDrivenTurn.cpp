#include "Game/Actor/Action/actionAnimeDrivenTurn.h"
#include <cmath>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnimeDrivenTurn::AnimeDrivenTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimeDrivenTurn::~AnimeDrivenTurn() = default;

bool AnimeDrivenTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: direction validation, angle math and animation setup scheduling.
void AnimeDrivenTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    sead::Matrix34f transform;
    controller->sub_7100F626E8(&transform);
    controller->sub_7100F5EDBC(transform.getBase(2));
    const auto* target = mTargetPos_d;
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    sead::Vector3f direction(target->x - position.x, 0.0f, target->z - position.z);
    direction.normalize();
    if (ksys::util::isVectorInvalid(direction) ||
        (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f))
        direction = controller->get64();
    const auto& forward = controller->get64();
    f32 dot = direction.dot(forward);
    if (dot < -1.0f || dot > 1.0f)
        dot = -1.0f;
    f32 angle = std::acos(dot);
    const f32 sign = direction.z * forward.x - direction.x * forward.z >= 0.0f ? 1.0f : -1.0f;
    if (angle < 0.0f)
        angle = 0.0f;
    else if (angle > *mRotateAngleMax_s)
        angle = *mRotateAngleMax_s;
    if (angle <= *mFinishAngleRange_s) {
        setFinished();
        return;
    }
    as_list->x_6(1, 0, 0.0f);
    as_list->x_6(2, 0, 0.0f);
    as_list->x_6(9, 0, sead::Mathf::rad2deg(-angle * sign));
    _84 = false;
    const s32 frames = *mAllowChangeableFrame_s;
    if (frames >= 0) {
        _78.reset(static_cast<f32>(frames) + 0.5f);
        if (_78.value < 1.0f)
            mFlags.set(Flag::Changeable);
    } else {
        _78.reset(static_cast<f32>(frames), 0.0f);
    }
    if (mASKeyName_s.isEmpty()) {
        setFailed();
        return;
    }
    if (*mIsIgnoreSameAS_s && as_list->x_1(0, 0) == mASKeyName_s)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, mASKeyName_s, 0, 0, true);
    if (mActor->getModel())
        mActor->getASList()->sub_710115BAF8(mTargetBone_s);
}

void AnimeDrivenTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimeDrivenTurn::loadParams_() {
    getStaticParam(&mAllowChangeableFrame_s, "AllowChangeableFrame");
    getStaticParam(&mAnimPlayRate_s, "AnimPlayRate");
    getStaticParam(&mFinishAngleRange_s, "FinishAngleRange");
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsAllowAnimeDrivenNoChangeAS_s, "IsAllowAnimeDrivenNoChangeAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: direction validation, angle math and animation branch layout.
void AnimeDrivenTurn::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    m32();
    if (mASKeyName_s == as_list->x_1(0, 0) && isFinishedAS(0, 0))
        setFinished();
    if (isFinished() || isFailed()) {
        act::sub_7100E7F318(as_list, controller, 1.0f);
        return;
    }
    const auto* target = mTargetPos_d;
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    sead::Vector3f direction(target->x - position.x, 0.0f, target->z - position.z);
    direction.normalize();
    if (ksys::util::isVectorInvalid(direction) ||
        (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f))
        direction = controller->get64();
    const auto& forward = controller->get64();
    f32 dot = direction.dot(forward);
    if (dot < -1.0f || dot > 1.0f)
        dot = -1.0f;
    const f32 raw_angle = std::acos(dot);
    const f32 sign = direction.z * forward.x - direction.x * forward.z >= 0.0f ? 1.0f : -1.0f;
    f32 angle = raw_angle;
    if (angle < 0.0f)
        angle = 0.0f;
    else if (angle > *mRotateAngleMax_s)
        angle = *mRotateAngleMax_s;
    if (as_list->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (*mIsAllowAnimeDrivenNoChangeAS_s)
            act::sub_7100E7F318(as_list, controller, 1.0f);
        if (raw_angle <= *mFinishAngleRange_s)
            _84 = true;
    } else if (raw_angle <= *mFinishAngleRange_s || _84) {
        act::sub_7100E7F318(as_list, controller, 1.0f);
        _84 = false;
        setFinished();
    } else {
        as_list->x_6(1, 0, 0.0f);
        as_list->x_6(2, 0, 0.0f);
        as_list->x_6(9, 0, sead::Mathf::rad2deg(-angle * sign));
        act::sub_7100E7F318(as_list, controller, 1.0f);
    }
}

void AnimeDrivenTurn::m32() {
    _78.update();
    if (_78.hasEnded(0.0f))
        mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
