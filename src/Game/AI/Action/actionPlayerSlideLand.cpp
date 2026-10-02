#include "Game/AI/Action/actionPlayerSlideLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSlideLand::PlayerSlideLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSlideLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SlideLand", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value *= 0.5f;
    player->_20bc.prev_value = player->_20bc.value;
}

// NON_MATCHING: the original loads mActor before the x_5() result
void PlayerSlideLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1c68 =
        static_cast<ksys::act::Player*>(mActor)->x_5().value;
}

void PlayerSlideLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerSlideLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
