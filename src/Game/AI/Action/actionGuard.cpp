#include "Game/AI/Action/actionGuard.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

Guard::Guard(const InitArg& arg) : TakeHitImpactForce(arg) {}

void Guard::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void Guard::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mRotSubsAngRate_s, "RotSubsAngRate");
}

void Guard::calc_() {
    if (auto* controller = mActor->getCharacterController()) {
        sub_7100738660(controller, 0.8f);
        TakeHitImpactForce::calc_();
    }
}

bool Guard::isChangeable() const {
    return true;
}

void Guard::m38() {
    playAS("GuardShock", false, 0, 0, -1.0f);
}

}  // namespace uking::action
