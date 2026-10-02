#include "Game/AI/Behavior/behaviorAddRigidBodyToWorld.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

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

void AddRigidBodyToWorld::m9() {
    if (!_40)
        return;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(mRigidBodySetName_s)) {
            set->removeFromWorld();
            if (*mEnableNavMeshCut_s)
                physics->sub_7100FC01B0();
        }
    }
    _40 = false;
}

void AddRigidBodyToWorld::loadParams() {
    getStaticParam(&mEnableNavMeshCut_s, "EnableNavMeshCut");
    getStaticParam(&mRigidBodySetName_s, "RigidBodySetName");
}

}  // namespace uking::behavior
