#include "Game/AI/Behavior/behaviorNpcClerkCheck.h"

namespace uking::behavior {

NpcClerkCheck::NpcClerkCheck(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NpcClerkCheck::~NpcClerkCheck() = default;

bool NpcClerkCheck::m6(sead::Heap* heap) {
    return true;
}

void NpcClerkCheck::m8() {}

void NpcClerkCheck::m9() {}

void NpcClerkCheck::loadParams() {

}

}  // namespace uking::behavior
