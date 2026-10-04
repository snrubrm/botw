#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RandomMoveAction::RandomMoveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void RandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _34 = 1.0f;
    if (auto* nav = mActor->m45()) {
        mActor->getCharacterController();
        nav->sub_7100F76790();
        nav->inlineReset();
    }
}

void RandomMoveAction::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76778();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(0.0f);
    }
}

void RandomMoveAction::m33(void*, ksys::phys::NavMeshCharacter* nav) {
    nav->sub_7100F76790();
}

void RandomMoveAction::loadParams_() {
    getStaticParam(&mIsSuccessWhenGoalReached_s, "IsSuccessWhenGoalReached");
}

void RandomMoveAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
