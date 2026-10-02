#include "Game/AI/Action/actionPlayerCutDash.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutDash::PlayerCutDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutDash::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutDash::loadParams_() {
    getStaticParam(&mSearchAngle_s, "SearchAngle");
}

void PlayerCutDash::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutDash::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
