#include "Game/AI/Behavior/behaviorSandwormTeraPach.h"

namespace uking::behavior {

SandwormTeraPach::SandwormTeraPach(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool SandwormTeraPach::m6(sead::Heap* heap) {
    return true;
}

void SandwormTeraPach::m9() {}

void SandwormTeraPach::loadParams() {
    getStaticParam(&mNode1_s, "Node1");
}

}  // namespace uking::behavior
