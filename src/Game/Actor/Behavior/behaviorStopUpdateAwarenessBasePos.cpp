#include "Game/Actor/Behavior/behaviorStopUpdateAwarenessBasePos.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

StopUpdateAwarenessBasePos::StopUpdateAwarenessBasePos(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

StopUpdateAwarenessBasePos::~StopUpdateAwarenessBasePos() = default;

bool StopUpdateAwarenessBasePos::init_(sead::Heap* heap) {
    return true;
}

void StopUpdateAwarenessBasePos::calc() {}

void StopUpdateAwarenessBasePos::loadParams() {

}

void StopUpdateAwarenessBasePos::enter() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 |= 0x10;
}

void StopUpdateAwarenessBasePos::leave() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 &= ~0x10;
}

}  // namespace uking::behavior
