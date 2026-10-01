#include "Game/AI/Action/actionEventRecoverPlayerCondition.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

EventRecoverPlayerCondition::EventRecoverPlayerCondition(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerCondition::~EventRecoverPlayerCondition() = default;

bool EventRecoverPlayerCondition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventRecoverPlayerCondition::oneShot_() {
    if (auto* player_info = ksys::act::PlayerInfo::instance())
        player_info->recoverCondition();
    return true;
}

void EventRecoverPlayerCondition::loadParams_() {}

}  // namespace uking::action
