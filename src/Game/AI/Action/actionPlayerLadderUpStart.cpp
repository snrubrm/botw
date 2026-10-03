#include "Game/AI/Action/actionPlayerLadderUpStart.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

PlayerLadderUpStart::PlayerLadderUpStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderUpStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderUpStart::leave_() {}

void PlayerLadderUpStart::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerLadderUpStart::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c += player->_1828 * ksys::VFR::instance()->getDeltaFrame();
    player = static_cast<ksys::act::Player*>(mActor);
    player->sub_7100892100(player->_181c);
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

bool PlayerLadderUpStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
