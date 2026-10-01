#include "Game/AI/Action/actionResetPlayerPullSwordStartLife.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

ResetPlayerPullSwordStartLife::ResetPlayerPullSwordStartLife(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetPlayerPullSwordStartLife::~ResetPlayerPullSwordStartLife() = default;

bool ResetPlayerPullSwordStartLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ResetPlayerPullSwordStartLife::oneShot_() {
    if (auto* player_info = ksys::act::PlayerInfo::instance())
        player_info->resetLifeToBeforeSwordPull();
    return true;
}

void ResetPlayerPullSwordStartLife::loadParams_() {}

}  // namespace uking::action
