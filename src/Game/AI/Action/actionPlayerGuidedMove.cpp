#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGuidedMove::PlayerGuidedMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuidedMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuidedMove::leave_() {}

void PlayerGuidedMove::loadParams_() {
    getStaticParam(&mDecSpdDist_s, "DecSpdDist");
    getDynamicParam(&mStickValue_d, "StickValue");
    getStaticParam(&mForceTurnDist_s, "ForceTurnDist");
}

void PlayerGuidedMove::calc_() {
    PlayerAction::calc_();
}

// NON_MATCHING: the original retains a dead actor predicate load before comparing the animation name.
void PlayerGuidedMove::sub_71007E8D28() {
    if (mActor->getASList()->x_1(0, 0) != "DemoWait")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    _38 = 0;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    setFinished();
}

bool PlayerGuidedMove::isChangeable() const {
    return false;
}

}  // namespace uking::action
