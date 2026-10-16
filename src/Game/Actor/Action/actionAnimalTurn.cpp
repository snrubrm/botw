#include "Game/Actor/Action/actionAnimalTurn.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/Action/actionForkAnimalASPlay.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

AnimalTurn::AnimalTurn(const InitArg& arg) : PlayASForAnimalUnit(arg) {}

AnimalTurn::~AnimalTurn() = default;

bool AnimalTurn::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

// NON_MATCHING: register allocation / operand order of the direction vector (the original keeps dx / dz in s8 / s9, loads
// the position before the target and tests the components of `dir` for NaN in the order y, x, z).
void AnimalTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (!as_list || !controller || !rideable) {
        setFailed();
        return;
    }

    sead::Vector3f position;
    sead::Matrix34f mtx;
    controller->sub_7100F626E8(&mtx);
    position = {mtx.m[0][2], mtx.m[1][2], mtx.m[2][2]};
    controller->sub_7100F5EDBC(position);
    const sead::Vector3f* target = mTargetPos_d;
    controller->sub_7100F5F6E0(&position);

    sead::Vector3f dir = *target;
    dir -= position;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.isNan() || (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f))
        dir = controller->get64();

    const sead::Vector3f& forward = controller->get64();
    const f32 angle = sead::Mathf::clamp(sead::Mathf::acos(sead::Mathf::clamp(dir.dot(forward), -1.0f, 1.0f)),
                                         0.0f, *mRotateAngleMax_s);
    const f32 cross = dir.z * forward.x - dir.x * forward.z;
    const f32 sign = cross >= 0.0f ? 1.0f : -1.0f;
    if (angle > *mFinishAngleRange_s) {
        as_list->x_6(1, 0, 0.0f);
        as_list->x_6(2, 0, 0.0f);
        as_list->x_6(9, 0, -sead::Mathf::rad2deg(sign * angle));
        PlayASForAnimalUnit::enter_(params);
    } else {
        sub_710013D91C();
        setFinished();
    }
}

void AnimalTurn::leave_() {
    PlayASForAnimalUnit::leave_();
}

void AnimalTurn::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mAnimPlayRate_s, "AnimPlayRate");
    getStaticParam(&mFinishAngleRange_s, "FinishAngleRange");
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: load order of the target / position and of the forward vector (same differences as enter_).
void AnimalTurn::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (!as_list || !controller || !rideable) {
        setFailed();
        return;
    }

    m32();
    if (mASKeyName_s == as_list->x_1(0, 0) && isFinishedAS(0, 0)) {
        sub_710013D91C();
        setFinished();
    }
    if (isFinished() || isFailed()) {
        act::sub_7100E7F698(rideable, as_list, controller);
        return;
    }
    if (as_list->x(0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return;

    const sead::Vector3f* target = mTargetPos_d;
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    sead::Vector3f dir = *target;
    dir -= position;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.isNan() || (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f))
        dir = controller->get64();

    const sead::Vector3f& forward = controller->get64();
    f32 angle = sead::Mathf::acos(sead::Mathf::clamp(dir.dot(forward), -1.0f, 1.0f));
    const f32 cross = dir.z * forward.x - dir.x * forward.z;
    const f32 sign = cross >= 0.0f ? 1.0f : -1.0f;
    if (angle <= *mFinishAngleRange_s) {
        sub_710013D91C();
        setFinished();
    } else {
        angle = sead::Mathf::clamp(angle, 0.0f, *mRotateAngleMax_s);
        as_list->x_6(1, 0, 0.0f);
        as_list->x_6(2, 0, 0.0f);
        as_list->x_6(9, 0, -sead::Mathf::rad2deg(sign * angle));
        act::sub_7100E7F698(rideable, as_list, controller);
    }
}

}  // namespace uking::action
