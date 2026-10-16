#include "Game/Actor/Behavior/behaviorRemoveNavMeshObj.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

RemoveNavMeshObj::RemoveNavMeshObj(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RemoveNavMeshObj::~RemoveNavMeshObj() = default;

bool RemoveNavMeshObj::init_(sead::Heap* heap) {
    return true;
}

void RemoveNavMeshObj::calc() {}

void RemoveNavMeshObj::enter() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC01B0();
}

void RemoveNavMeshObj::leave() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC012C(nullptr);
}

void RemoveNavMeshObj::loadParams() {

}

}  // namespace uking::behavior
