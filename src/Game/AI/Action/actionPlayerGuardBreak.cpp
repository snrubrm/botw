#include "Game/AI/Action/actionPlayerGuardBreak.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGuardBreak::PlayerGuardBreak(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardBreak::leave_() {}

void PlayerGuardBreak::loadParams_() {}

void PlayerGuardBreak::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        static_cast<ksys::act::Player*>(mActor)->_cec.resetBit(1);
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGuardBreak::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
