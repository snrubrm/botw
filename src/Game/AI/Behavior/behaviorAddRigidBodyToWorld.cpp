#include "Game/AI/Behavior/behaviorAddRigidBodyToWorld.h"

namespace uking::behavior {

AddRigidBodyToWorld::AddRigidBodyToWorld(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
AddRigidBodyToWorld::~AddRigidBodyToWorld() {
    ;
}

bool AddRigidBodyToWorld::m6(sead::Heap* heap) {
    return true;
}

void AddRigidBodyToWorld::m7() {}

void AddRigidBodyToWorld::loadParams() {
    getStaticParam(&mEnableNavMeshCut_s, "EnableNavMeshCut");
    getStaticParam(&mRigidBodySetName_s, "RigidBodySetName");
}

}  // namespace uking::behavior
