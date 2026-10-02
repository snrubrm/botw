#include "Game/AI/Behavior/behaviorRemoveNavMeshObj.h"

namespace uking::behavior {

RemoveNavMeshObj::RemoveNavMeshObj(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RemoveNavMeshObj::~RemoveNavMeshObj() = default;

bool RemoveNavMeshObj::m6(sead::Heap* heap) {
    return true;
}

void RemoveNavMeshObj::m7() {}

void RemoveNavMeshObj::loadParams() {

}

}  // namespace uking::behavior
