#include "Game/AI/Action/actionPlayerElectric.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerElectric::PlayerElectric(const InitArg& arg) : PlayerAction(arg) {}

void PlayerElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerElectric::leave_() {
    PlayerAction::leave_();
}

void PlayerElectric::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

// NON_MATCHING: the original calls `_2550.m13(4)` through the vtable (ours devirtualises the member object) and
// reloads `mActor` separately in both arms after stillAlive() (ours hoists the load).
void PlayerElectric::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0) {
        if (player->isSurfingOnGround())
            static_cast<ksys::act::Player*>(mActor)->_2550.m13(4);
    } else {
        player->_20bc.value = 0;
        player->_20bc.prev_value = 0;
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        if (!static_cast<ksys::act::Player*>(mActor)->_2550._8.isOnBit(4))
            setFinished();
    } else {
        uking::callPlayerGameOverDemo(mActor);
    }
}

bool PlayerElectric::isChangeable() const {
    return false;
}

}  // namespace uking::action
