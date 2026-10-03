#include "Game/AI/Action/actionPlayerLookAtObjectNow.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLookAtObjectNow::PlayerLookAtObjectNow(const InitArg& arg) : PlayerLookAtObject(arg) {}

PlayerLookAtObjectNow::~PlayerLookAtObjectNow() = default;

bool PlayerLookAtObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObject::init_(heap);
}

bool PlayerLookAtObjectNow::oneShot_() {
    if (PlayerLookAtObject::oneShot_()) {
        static_cast<ksys::act::Player*>(mActor)->_2d64 = true;
        return true;
    }
    return false;
}

void PlayerLookAtObjectNow::loadParams_() {
    PlayerLookAtObject::loadParams_();
}

}  // namespace uking::action
