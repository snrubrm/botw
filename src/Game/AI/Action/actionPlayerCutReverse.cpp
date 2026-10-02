#include "Game/AI/Action/actionPlayerCutReverse.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutReverse::PlayerCutReverse(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutReverse::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutReverse::leave_() {}

void PlayerCutReverse::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerCutReverse::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
