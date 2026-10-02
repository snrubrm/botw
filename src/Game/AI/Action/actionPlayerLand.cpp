#include "Game/AI/Action/actionPlayerLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerLand::PlayerLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLand::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        auto* proc = player->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
