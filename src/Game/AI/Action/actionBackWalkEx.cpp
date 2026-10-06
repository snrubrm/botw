#include "Game/AI/Action/actionBackWalkEx.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

BackWalkEx::BackWalkEx(const InitArg& arg) : BackWalkBase(arg) {}

BackWalkEx::~BackWalkEx() = default;

bool BackWalkEx::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void BackWalkEx::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
    const f32 speed = mActor->getVelocity().length();
    _b0.value = speed;
    _b0.prev_value = speed;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(sead::Vector3f(speed, speed, speed).length() * 30.0f);
        sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
    }
}

void BackWalkEx::leave_() {
    BackWalkBase::leave_();
}

void BackWalkEx::loadParams_() {
    BackWalkBase::loadParams_();
}

void BackWalkEx::calc_() {
    BackWalkBase::calc_();
}

void BackWalkEx::m32(ksys::phys::CharacterController* controller) {
    _b0.lerp(*mParams.mDecelRatio_s * *mParams.mSpeed_s, 0.1f);
    _b0.updateStats();
    controller->sub_7100F5E7F0(_b0.value * 30.0f);
    sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
}

void BackWalkEx::m33(ksys::phys::CharacterController* controller) {
    _b0.lerp(f32(*mParams.mSpeed_s), 0.08f);
    _b0.updateStats();
    controller->sub_7100F5E7F0(_b0.value * 30.0f);
    sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
}

}  // namespace uking::action
