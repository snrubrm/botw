#include "Game/AI/Action/actionPlayerWakeBoardEnd.h"

#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"

namespace uking::action {

PlayerWakeBoardEnd::PlayerWakeBoardEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWakeBoardEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Wait", true, -1.0f);
    auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
    if (surfing && surfing->_60.isOn(1)) {
        surfing->sub_7100EBB518();
        mActor->resetConnectedCalcChild(false);
        static_cast<ksys::act::Player*>(mActor)->someFloatCalc(2.0f, {0, 1, 0});
    }
    static_cast<ksys::act::Player*>(mActor)->sub_710088A854();
}

void PlayerWakeBoardEnd::leave_() {}

void PlayerWakeBoardEnd::loadParams_() {}

void PlayerWakeBoardEnd::calc_() {
    setFinished();
}

bool PlayerWakeBoardEnd::isChangeable() const {
    return false;
}

}  // namespace uking::action
