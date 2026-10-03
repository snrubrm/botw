#include "Game/AI/Action/actionLastBossFlyWaitTurnToTarget.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossFlyWaitTurnToTarget::LastBossFlyWaitTurnToTarget(const InitArg& arg)
    : LastBossFlyWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
LastBossFlyWaitTurnToTarget::~LastBossFlyWaitTurnToTarget() {
    ;
}

void LastBossFlyWaitTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossFlyWait::enter_(params);
    _ec.value = _ec.prev_value = mActor->getAngVelocity().length();
}

void LastBossFlyWaitTurnToTarget::leave_() {
    LastBossFlyWait::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    _f8 = false;
}

void LastBossFlyWaitTurnToTarget::loadParams_() {
    LastBossFlyWait::loadParams_();
    getStaticParam(&mTurnStartDiffAng_s, "TurnStartDiffAng");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mTurnASName_s, "TurnASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::action
