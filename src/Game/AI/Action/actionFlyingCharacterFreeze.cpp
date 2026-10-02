#include "Game/AI/Action/actionFlyingCharacterFreeze.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterFreeze::FlyingCharacterFreeze(const InitArg& arg) : FlyingCharacterReaction(arg) {}

bool FlyingCharacterFreeze::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
}

void FlyingCharacterFreeze::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeze::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mStopTime_s, "StopTime");
}

void FlyingCharacterFreeze::calc_() {
    FlyingCharacterReaction::calc_();
}

// NON_MATCHING: sub_7100F5F0E4 returns a 4-byte struct in the original (the result is spilled to the stack)
void FlyingCharacterFreeze::m34(ksys::phys::CharacterController* controller) {
    if (_78.value <= sead::Mathf::epsilon()) {
        if (controller->sub_7100F5F0E4() != ksys::act::MotionType::_1)
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
        return;
    }
    _78.update();
    sub_71007377D4(controller, 0.0f);
    sub_7100738660(controller, 0.0f);
}

}  // namespace uking::action
