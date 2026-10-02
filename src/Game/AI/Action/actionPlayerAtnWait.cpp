#include "Game/AI/Action/actionPlayerAtnWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerAtnWait::PlayerAtnWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

// NON_MATCHING: the original does not fold &mActor into a pre-indexed load
void PlayerAtnWait::leave_() {
    if (mActor->getASList()->x_1(1, 1) == "WaitAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
}

void PlayerAtnWait::loadParams_() {
    getStaticParam(&mAtnTurnDiffAng_s, "AtnTurnDiffAng");
}

void PlayerAtnWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerAtnWait::isChangeable() const {
    return true;
}

}  // namespace uking::action
