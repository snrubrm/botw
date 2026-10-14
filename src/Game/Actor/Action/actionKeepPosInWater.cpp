#include "Game/Actor/Action/actionKeepPosInWater.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

KeepPosInWater::KeepPosInWater(const InitArg& arg) : WaitBase(arg) {}

KeepPosInWater::~KeepPosInWater() = default;

bool KeepPosInWater::init_(sead::Heap* heap) {
    return WaitBase::init_(heap);
}

void KeepPosInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitBase::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->sub_7100F5E7F0(0.0f);
    playAS(mASKeyName_s.cstr(), true, 0, 0, -1.0f);
}

void KeepPosInWater::leave_() {
    WaitBase::leave_();
}

void KeepPosInWater::loadParams_() {
    WaitBase::loadParams_();
    getStaticParam(&mForceTurnLimitSpeedStream_s, "ForceTurnLimitSpeedStream");
    getStaticParam(&mChaceFrontRate_s, "ChaceFrontRate");
    getStaticParam(&mChaceAngSpeedMax_s, "ChaceAngSpeedMax");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

// NON_MATCHING: stack layout (the original reuses the gravity slot for the matrix) and dot-product scheduling.
void KeepPosInWater::calc_() {
    WaitBase::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sead::Matrix34f mtx;
    controller->sub_7100F626E8(&mtx);
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    sead::Vector3f dir = velocity;
    dir.normalize();
    const f32 rate = (dir.x * mtx(0, 2) + dir.y * mtx(1, 2) + dir.z * mtx(2, 2) + 1.0f) * 0.5f;
    sub_71007377D4(controller, sead::Mathf::clamp(rate, 0.0f, 1.0f));

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    sead::Vector3f stream = controller->get180();
    const f32 speed = stream.normalize();
    if (mActor->get68f() && speed > *mForceTurnLimitSpeedStream_s) {
        sead::Vector3f target = -stream;
        ksys::util::sub_71011EE70C(&front, &target, *mChaceFrontRate_s, *mChaceAngSpeedMax_s,
                                   sead::Mathf::deg2rad(0.1f));
        front.normalize();
    }
    controller->sub_7100F5FDF0(front);
}

}  // namespace uking::action
