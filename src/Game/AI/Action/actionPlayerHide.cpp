#include "Game/AI/Action/actionPlayerHide.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerHide::PlayerHide(const InitArg& arg) : PlayerAction(arg) {}

PlayerHide::~PlayerHide() = default;

bool PlayerHide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

bool PlayerHide::oneShot_() {
    mActor->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_20, *mHidden_s);
    return true;
}

void PlayerHide::loadParams_() {
    getStaticParam(&mHidden_s, "Hidden");
}

}  // namespace uking::action
