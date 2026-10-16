#include "Game/Actor/Behavior/behaviorClearFadeInCreate.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

ClearFadeInCreate::ClearFadeInCreate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ClearFadeInCreate::~ClearFadeInCreate() = default;

bool ClearFadeInCreate::init_(sead::Heap* heap) {
    return true;
}

void ClearFadeInCreate::leave() {}

void ClearFadeInCreate::enter() {
    mActor->clearFadeInCreate();
}

}  // namespace uking::behavior
