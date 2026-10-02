#include "Game/AI/Action/actionPlayerDeadWait.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerDeadWait::PlayerDeadWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool b186 = static_cast<ksys::act::Player*>(mActor)->m186();
    const bool b_cf4 = static_cast<ksys::act::Player*>(mActor)->_cf4.isOnBit(1);
    const bool b188 = static_cast<ksys::act::Player*>(mActor)->m188();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x100);
    if (b186)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x80);
    if (b_cf4)
        static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2);
    if (b188)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
}

void PlayerDeadWait::leave_() {}

void PlayerDeadWait::calc_() {
    callPlayerGameOverDemo(mActor);
}

bool PlayerDeadWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
