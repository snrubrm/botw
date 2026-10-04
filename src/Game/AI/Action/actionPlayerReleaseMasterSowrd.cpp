#include "Game/AI/Action/actionPlayerReleaseMasterSowrd.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerReleaseMasterSowrd::PlayerReleaseMasterSowrd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerReleaseMasterSowrd::~PlayerReleaseMasterSowrd() = default;

bool PlayerReleaseMasterSowrd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool PlayerReleaseMasterSowrd::oneShot_() {
    if (auto* player = sead::DynamicCast<ksys::act::Player>(mActor))
        player->releaseWeapon(0);
    return true;
}

void PlayerReleaseMasterSowrd::loadParams_() {}

}  // namespace uking::action
