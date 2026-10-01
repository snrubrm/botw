#include "Game/AI/Action/actionNPCWaitAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCWaitAction::NPCWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void NPCWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCWaitAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCWaitAction::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

void NPCWaitAction::calc_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    else
        setFailed();
}

}  // namespace uking::action
