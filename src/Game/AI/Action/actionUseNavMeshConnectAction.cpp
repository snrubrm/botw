#include "Game/AI/Action/actionUseNavMeshConnectAction.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

UseNavMeshConnectAction::UseNavMeshConnectAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

UseNavMeshConnectAction::~UseNavMeshConnectAction() = default;

bool UseNavMeshConnectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UseNavMeshConnectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("NavMeshConnect"))
            set->addToWorld();
    }
}

void UseNavMeshConnectAction::leave_() {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("NavMeshConnect"))
            set->removeFromWorld();
    }
}

void UseNavMeshConnectAction::loadParams_() {}

void UseNavMeshConnectAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
