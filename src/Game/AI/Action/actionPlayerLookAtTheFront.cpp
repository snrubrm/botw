#include "Game/AI/Action/actionPlayerLookAtTheFront.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLookAtTheFront::PlayerLookAtTheFront(const InitArg& arg) : PlayerAction(arg) {}

PlayerLookAtTheFront::~PlayerLookAtTheFront() = default;

bool PlayerLookAtTheFront::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

bool PlayerLookAtTheFront::oneShot_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(*mIsValid_d, 0, &sead::Vector3f::zero, nullptr,
                                                           &sead::Vector3f::zero);
    return true;
}

void PlayerLookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

}  // namespace uking::action
