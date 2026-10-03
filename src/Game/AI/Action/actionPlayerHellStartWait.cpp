#include "Game/AI/Action/actionPlayerHellStartWait.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_71008ba8d8.h"

namespace uking::action {

PlayerHellStartWait::PlayerHellStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerHellStartWait::~PlayerHellStartWait() = default;

void PlayerHellStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHellStartWait::leave_() {
    ksys::evt::Manager::instance()->_1d2f4 &= ~1u;
}

void PlayerHellStartWait::calc_() {
    static_cast<ksys::act::Player*>(mActor)->setCE0Locked(0x8);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    uking::callPlayerRespawnEvent(mActor);
    static_cast<ksys::act::Player*>(mActor)->_c4c.set(0x10);
}

bool PlayerHellStartWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
