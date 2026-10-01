#include "Game/AI/Action/actionDefEscapeFreeMoveAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DefEscapeFreeMoveAction::DefEscapeFreeMoveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefEscapeFreeMoveAction::~DefEscapeFreeMoveAction() = default;

bool DefEscapeFreeMoveAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefEscapeFreeMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DefEscapeFreeMoveAction::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(_b4);
}

void DefEscapeFreeMoveAction::loadParams_() {
    getStaticParam(&mRunAwaySpeed_s, "RunAwaySpeed");
    getStaticParam(&mRunAwayAngleSpeed_s, "RunAwayAngleSpeed");
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mRunAwayDistanceMin_s, "RunAwayDistanceMin");
    getStaticParam(&mRunAwayHeightOffset_s, "RunAwayHeightOffset");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mInWater_s, "InWater");
    getStaticParam(&mIsSnake_s, "IsSnake");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DefEscapeFreeMoveAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
