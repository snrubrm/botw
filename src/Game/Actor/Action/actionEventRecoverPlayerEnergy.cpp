#include "Game/Actor/Action/actionEventRecoverPlayerEnergy.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::action {

EventRecoverPlayerEnergy::EventRecoverPlayerEnergy(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRecoverPlayerEnergy::~EventRecoverPlayerEnergy() = default;

bool EventRecoverPlayerEnergy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventRecoverPlayerEnergy::oneShot_() {
    if (auto* player_info = uking::act::PlayerInfo::instance())
        player_info->recoverStamina();
    return true;
}

void EventRecoverPlayerEnergy::loadParams_() {}

}  // namespace uking::action
