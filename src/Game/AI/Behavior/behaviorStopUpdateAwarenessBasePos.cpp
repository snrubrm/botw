#include "Game/AI/Behavior/behaviorStopUpdateAwarenessBasePos.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

StopUpdateAwarenessBasePos::StopUpdateAwarenessBasePos(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

StopUpdateAwarenessBasePos::~StopUpdateAwarenessBasePos() = default;

bool StopUpdateAwarenessBasePos::m6(sead::Heap* heap) {
    return true;
}

void StopUpdateAwarenessBasePos::m7() {}

void StopUpdateAwarenessBasePos::loadParams() {

}

void StopUpdateAwarenessBasePos::m8() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 |= 0x10;
}

void StopUpdateAwarenessBasePos::m9() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 &= ~0x10;
}

}  // namespace uking::behavior
