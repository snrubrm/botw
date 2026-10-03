#include "Game/AI/Action/actionPlayerAtnMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerAtnMove::PlayerAtnMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerAtnMove::leave_() {
    if (mActor->getASList()->x_1(1, 1) == "MoveAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (mActor->getASList()->x_1(1, 1) == "MoveUnsteadyUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerAtnMove::loadParams_() {}

void PlayerAtnMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerAtnMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
