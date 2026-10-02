#include "Game/AI/Action/actionFlyingCharacterFreeze.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

FlyingCharacterFreeze::FlyingCharacterFreeze(const InitArg& arg) : FlyingCharacterReaction(arg) {}

FlyingCharacterFreeze::~FlyingCharacterFreeze() = default;

bool FlyingCharacterFreeze::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    _78 = ksys::Timer(*mStopTime_s, *mStopTime_s);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.set(0x800);
}

void FlyingCharacterFreeze::leave_() {
    FlyingCharacterReaction::leave_();
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.reset(0x800);
}

bool FlyingCharacterFreeze::isFinished() const {
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(3))
        return true;
    return false;
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
