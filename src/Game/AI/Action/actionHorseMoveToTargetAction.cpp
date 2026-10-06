#include "Game/AI/Action/actionHorseMoveToTargetAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

HorseMoveToTargetAction::HorseMoveToTargetAction(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

bool HorseMoveToTargetAction::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void HorseMoveToTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
    mActor->m132();                      // discarded call
    mActor->getCharacterController();  // discarded call
    if (auto* nav = mActor->m45()) {
        if (*mIsCancelRequestedPathFirst_s)
            nav->inlineReset();
        if (mTargetPos_d && !mTargetPos_d->isNan()) {
            nav->sub_7100F75F8C(*mTargetPos_d);
            nav->inlineClearTargets();
        }
    }
}

void HorseMoveToTargetAction::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void HorseMoveToTargetAction::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseMoveToTargetAction::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
