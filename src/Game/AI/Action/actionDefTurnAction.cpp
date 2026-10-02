#include "Game/AI/Action/actionDefTurnAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

DefTurnAction::DefTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefTurnAction::~DefTurnAction() = default;

bool DefTurnAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = _60 = *mWaitRotate_s;
    _64 = -1.0f;
    _68 = *mWaitRotate_s - 1.0f;
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mASKeyName_s, 0, 0, true);
}

void DefTurnAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void DefTurnAction::loadParams_() {
    getStaticParam(&mWaitRotate_s, "WaitRotate");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DefTurnAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
