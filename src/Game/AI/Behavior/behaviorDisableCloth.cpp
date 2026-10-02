#include "Game/AI/Behavior/behaviorDisableCloth.h"

namespace uking::behavior {

DisableCloth::DisableCloth(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableCloth::~DisableCloth() = default;

bool DisableCloth::m6(sead::Heap* heap) {
    return true;
}

void DisableCloth::m7() {}

void DisableCloth::loadParams() {

}

}  // namespace uking::behavior
