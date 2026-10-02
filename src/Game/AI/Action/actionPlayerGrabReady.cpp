#include "Game/AI/Action/actionPlayerGrabReady.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabReady::PlayerGrabReady(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabReady::leave_() {}

void PlayerGrabReady::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0) {
        if (!player->getConnectedCalcChild())
            setFailed();
    } else {
        player->_17f0 = 1;
    }
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGrabReady::isChangeable() const {
    return false;
}

}  // namespace uking::action
