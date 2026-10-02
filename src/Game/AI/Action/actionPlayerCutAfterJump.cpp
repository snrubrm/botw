#include "Game/AI/Action/actionPlayerCutAfterJump.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutAfterJump::PlayerCutAfterJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutAfterJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutAfterJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutAfterJump::loadParams_() {}

void PlayerCutAfterJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutAfterJump::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
