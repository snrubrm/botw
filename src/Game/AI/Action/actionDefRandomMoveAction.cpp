#include "Game/AI/Action/actionDefRandomMoveAction.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DefRandomMoveAction::DefRandomMoveAction(const InitArg& arg) : RandomMoveAction(arg) {}

void DefRandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void DefRandomMoveAction::leave_() {
    RandomMoveAction::leave_();
}

void DefRandomMoveAction::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mMinMoveSpeed_s, "MinMoveSpeed");
    getStaticParam(&mMaxMoveDistance_s, "MaxMoveDistance");
    getStaticParam(&mMinMoveDistance_s, "MinMoveDistance");
    getStaticParam(&mMaxMoveAngle_s, "MaxMoveAngle");
    getStaticParam(&mIsUseBasepos_s, "IsUseBasepos");
    getDynamicParam(&mBasePos_d, "BasePos");
}

void DefRandomMoveAction::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* controller = mActor->getCharacterController();
    auto* nav = mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }
    if (!nav || !nav->_18) {
        controller->sub_7100F5E7F0(0.0f);
        return;
    }
    RandomMoveAction::calc_();
    controller->sub_7100F5FDF0(controller->get64());
}

}  // namespace uking::action
