#include "Game/Actor/Action/actionSmallDamageBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::action {

SmallDamageBase::SmallDamageBase(const InitArg& arg) : KnockBackHitImpactForce(arg) {}

void SmallDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackHitImpactForce::enter_(params);
}

void SmallDamageBase::calc_() {
    if (auto* controller = mActor->getCharacterController())
        sub_7100738660(controller, 0.5f);
    else if (auto* body = mActor->getMainBody())
        sub_7100738898(body, 0.5f);
    KnockBackHitImpactForce::calc_();
}

bool SmallDamageBase::isChangeable() const {
    return true;
}

}  // namespace uking::action
