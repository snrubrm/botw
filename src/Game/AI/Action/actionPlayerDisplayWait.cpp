#include "Game/AI/Action/actionPlayerDisplayWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerDisplayWait::PlayerDisplayWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDisplayWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Wait", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_17f8 = player->_1cb0;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    player = static_cast<ksys::act::Player*>(mActor);
    switch (player->_17f8) {
    case 0x35:
        if (!player->sub_71008921A8())
            setFinished();
        break;
    case 0x36:
        if (!player->sub_7100888294())
            setFinished();
        break;
    case 0x37:
        if (!player->sub_7100881EDC())
            setFinished();
        break;
    }
}

void PlayerDisplayWait::leave_() {}

void PlayerDisplayWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerDisplayWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
