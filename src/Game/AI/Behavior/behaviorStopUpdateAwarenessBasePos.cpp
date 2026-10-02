#include "Game/AI/Behavior/behaviorStopUpdateAwarenessBasePos.h"

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

}  // namespace uking::behavior
