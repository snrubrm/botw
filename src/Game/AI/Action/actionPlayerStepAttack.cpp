#include "Game/AI/Action/actionPlayerStepAttack.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerStepAttack::PlayerStepAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStepAttack::leave_() {
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerStepAttack::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerStepAttack::calc_() {
    PlayerAction::calc_();
}

bool PlayerStepAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
