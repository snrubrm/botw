#include "Game/AI/Behavior/behaviorRemoveNavMeshObj.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

RemoveNavMeshObj::RemoveNavMeshObj(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RemoveNavMeshObj::~RemoveNavMeshObj() = default;

bool RemoveNavMeshObj::m6(sead::Heap* heap) {
    return true;
}

void RemoveNavMeshObj::m7() {}

void RemoveNavMeshObj::m8() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC01B0();
}

void RemoveNavMeshObj::m9() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC012C(nullptr);
}

void RemoveNavMeshObj::loadParams() {

}

}  // namespace uking::behavior
