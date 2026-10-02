#include "Game/AI/Behavior/behaviorGuardFrontBarrier.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

GuardFrontBarrier::GuardFrontBarrier(const InitArg& arg) : GuardFrontBarrierBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GuardFrontBarrier::~GuardFrontBarrier() {
    ;
}

bool GuardFrontBarrier::m6(sead::Heap* heap) {
    return GuardFrontBarrierBase::m6(heap);
}

void GuardFrontBarrier::loadParams() {
    GuardFrontBarrierBase::loadParams();
    getStaticParam(&mTgtName_s, "TgtName");
}

void GuardFrontBarrier::m15(sead::Matrix34f* out) {
    *out = mActor->getMtx();
}

}  // namespace uking::behavior
