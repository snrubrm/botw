#include "Game/AI/Action/actionEventRecoverPlayerLife.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

EventRecoverPlayerLife::EventRecoverPlayerLife(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventRecoverPlayerLife::~EventRecoverPlayerLife() = default;

bool EventRecoverPlayerLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventRecoverPlayerLife::oneShot_() {
    if (auto* player_info = ksys::act::PlayerInfo::instance())
        player_info->recoverLife();
    return true;
}

void EventRecoverPlayerLife::loadParams_() {}

}  // namespace uking::action
