#include "Game/AI/Action/actionSetInstEventFlag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetInstEventFlag::SetInstEventFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetInstEventFlag::~SetInstEventFlag() = default;

bool SetInstEventFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetInstEventFlag::oneShot_() {
    if (mActor)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::InstEvent);
    return false;
}

void SetInstEventFlag::loadParams_() {}

}  // namespace uking::action
