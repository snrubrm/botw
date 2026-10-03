#include "Game/AI/Action/actionPlayerGuardJust.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

PlayerGuardJust::PlayerGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardJust", true, -1.0f);
}

void PlayerGuardJust::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return1(), act::Unk_71002edaec(1));
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x20);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x10000);
    auto* p2 = static_cast<ksys::act::Player*>(mActor);
    p2->_20bc.value = 0;
    p2->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerGuardJust::loadParams_() {
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

void PlayerGuardJust::calc_() {
    PlayerAction::calc_();
}

bool PlayerGuardJust::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
