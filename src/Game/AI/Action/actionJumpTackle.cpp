#include "Game/AI/Action/actionJumpTackle.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

// NON_MATCHING: store scheduling (param zeroing is sunk below the vtable store)
JumpTackle::JumpTackle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpTackle::~JumpTackle() = default;

bool JumpTackle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpTackle::leave_() {
    m33();
    sub_71005DA114(mActor, &_50);
}

void JumpTackle::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMinSpeed_s, "MinSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightMaxOffset_s, "JumpHeightMaxOffset");
    getStaticParam(&mIsFinishedAtPreLandFrame_s, "IsFinishedAtPreLandFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void JumpTackle::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _78 *= 0.978f;
    _78.updateStats();
    controller->sub_7100F5E7F0(_78.value * 30.0f);
    const sead::Vector3f axis = mActor->getMtx().getBase(2);
    sub_710072C1B4(controller, axis);
    sub_7100738660(controller, 0.75f);
    if (_90 && m34())
        setFinished();
    _90 = true;
}

bool JumpTackle::m34() {
    return ksys::act::sub_71007A4864(mActor, false);
}

}  // namespace uking::action
