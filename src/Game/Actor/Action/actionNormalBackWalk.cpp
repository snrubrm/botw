#include "Game/Actor/Action/actionNormalBackWalk.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

NormalBackWalk::NormalBackWalk(const InitArg& arg) : BackWalkBase(arg) {}

NormalBackWalk::~NormalBackWalk() = default;

bool NormalBackWalk::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void NormalBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
    const f32 speed = mActor->getVelocity().length();
    _b0.value = speed;
    _b0.prev_value = speed;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(sead::Vector3f(speed, speed, speed).length() * 30.0f);
        sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
    }
}

void NormalBackWalk::leave_() {
    BackWalkBase::leave_();
}

void NormalBackWalk::loadParams_() {
    BackWalkBase::loadParams_();
}

void NormalBackWalk::calc_() {
    BackWalkBase::calc_();
}

void NormalBackWalk::m32(ksys::phys::CharacterController* controller) {
    _b0.lerp(*mParams.mDecelRatio_s * *mParams.mSpeed_s, 0.1f);
    _b0.updateStats();
    controller->sub_7100F5E7F0(_b0.value * 30.0f);
    sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
}

void NormalBackWalk::m33(ksys::phys::CharacterController* controller) {
    _b0.lerp(f32(*mParams.mSpeed_s), 0.08f);
    _b0.updateStats();
    controller->sub_7100F5E7F0(_b0.value * 30.0f);
    sub_710072C1B4(controller, -mActor->getMtx().getBase(2));
}

}  // namespace uking::action
