#include "KingSystem/Physics/System/physRigidBodyDividedMeshShapeMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Resource/resHandle.h"
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

void RigidBodyDividedMeshShapeMgr::sub_7100FC6F00(res::Handle* handle) {
    if (!handle->requestedLoad())
        return;
    if (handle->isReadyOrNeedsParse())
        handle->parseResource(nullptr);
    auto* resource = sead::DynamicCast<TeraMeshRigidBodyResource>(handle->getResource());
    auto* body = resource ? resource->getRigidBody() : nullptr;
    if (body && body->isAddedToWorld())
        body->removeFromWorld();
    else
        handle->requestUnload();
}

}  // namespace ksys::phys
