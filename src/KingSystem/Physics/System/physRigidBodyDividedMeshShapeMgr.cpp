#include "KingSystem/Physics/System/physRigidBodyDividedMeshShapeMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"

namespace ksys::phys {

RigidBodyDividedMeshShapeMgr*
RigidBodyDividedMeshShapeMgr::makeInstance(const Config& config, sead::Heap* heap) {
    auto* mgr = new (heap, 8) RigidBodyDividedMeshShapeMgr(config, heap);
    System::instance()->setRigidBodyDividedMeshShapeMgr(mgr);
    return mgr;
}

void RigidBodyDividedMeshShapeMgr::addToWorld() {
    for (auto* body : mBoundaryBodies) {
        if (body)
            body->sub_7101223F80();
    }
}

}  // namespace ksys::phys
