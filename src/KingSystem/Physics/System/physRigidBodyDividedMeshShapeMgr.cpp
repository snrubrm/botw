#include "KingSystem/Physics/System/physRigidBodyDividedMeshShapeMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "Game/DLC/aocManager.h"
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

void RigidBodyDividedMeshShapeMgr::loadTeraMeshRigidBody(HandleInfo* info) {
    if (!info->handle.requestedLoad()) {
        res::LoadRequest request;
        request.mLaneId = 2;
        request.mRequester = "RigidBodyDividedMeshShapeMgr";
        request._22 = true;
        sead::FixedSafeString<256> path;
        path.format("%s/%d-%d.hktmrb", mName.cstr(), info->coordinates.x,
                    info->coordinates.y);
        if (uking::aoc::Manager::instance())
            request.mAocFileDevice = uking::aoc::Manager::instance()->getFileDeviceForTeraMesh(path);
        info->handle.requestLoad(path, &request, nullptr);
    }
    if (info->handle.isReadyOrNeedsParse())
        info->handle.parseResource(nullptr);
}

}  // namespace ksys::phys
