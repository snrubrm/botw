#include "Game/AI/Action/actionPlayerSlideLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSlideLand::PlayerSlideLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSlideLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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
