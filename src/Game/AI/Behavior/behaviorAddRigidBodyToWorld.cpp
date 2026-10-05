#include "Game/AI/Behavior/behaviorAddRigidBodyToWorld.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"

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

void AddRigidBodyToWorld::m8() {
    _40 = false;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    auto* set = physics->findBodyByName(mRigidBodySetName_s);
    if (!set) {
        mActor->getParam()->getRes().mActorLink->getUsers().getAIProgram();
        return;
    }
    set->addToWorld();
    if (*mEnableNavMeshCut_s)
        physics->sub_7100FC012C(nullptr);
    _40 = true;
}

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
