#include "Game/AI/Action/actionPlayerLadderMove.h"
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderMove::PlayerLadderMove(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: register allocation (the original loads _d1c into w10, ours into w9)
void PlayerLadderMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
    player = static_cast<ksys::act::Player*>(mActor);
    const f32 offset = sUnk_7101e7c5d0;
    if (player->_d1c) {
        player->_1810.y = player->_1810.y - offset;
        _28 = true;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderDown", true, -1.0f);
    } else {
        player->_1810.y = offset + player->_1810.y;
        _28 = false;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderUp", true, -1.0f);
    }
}

void PlayerLadderMove::leave_() {}

void PlayerLadderMove::loadParams_() {
    getStaticParam(&mDownMoveSpeed_s, "DownMoveSpeed");
}

void PlayerLadderMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
