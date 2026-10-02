#include "Game/AI/Action/actionPlayerCutHorseJumpLand.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutHorseJumpLand::PlayerCutHorseJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutHorseJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutHorseJumpLand::leave_() {
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutHorseJumpLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutHorseJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
