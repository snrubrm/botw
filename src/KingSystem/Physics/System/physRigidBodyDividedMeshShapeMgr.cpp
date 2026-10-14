#include "KingSystem/Physics/System/physRigidBodyDividedMeshShapeMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBodyResource.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"

namespace ksys::phys {

RigidBodyDividedMeshShapeMgr*
RigidBodyDividedMeshShapeMgr::makeInstance(const Config& config, sead::Heap* heap) {
    auto* mgr = new (heap, 8) RigidBodyDividedMeshShapeMgr(config, heap);
    System::instance()->setRigidBodyDividedMeshShapeMgr(mgr);
    return mgr;
}

// NON_MATCHING: the original stores the wrapper parameters in another order (terrain system first, _30 / _34 early).
RigidBodyDividedMeshShapeMgr::RigidBodyDividedMeshShapeMgr(const Config& config, sead::Heap* heap)
    : mName(config.name), mOrigin(config.origin), mTileSize(config.tile_size),
      mGridSize(config.size.x / config.tile_size.x, config.size.y / config.tile_size.y) {
    mHandles.tryAllocBuffer(9, heap);

    Unk_71025158e8::Param param;
    param.system = config.terrain_system;
    param._8 = 1;
    param._10 = 8;
    param.translation = config.translation;
    param.scale = config.scale;
    param._30 = 0;
    param._34 = false;
    for (s32 i = 0; i < 4; ++i) {
        param.index = i;
        mBoundaryBodies[i] = Unk_71025158e8::sub_7101223864(param, heap);
    }
}

RigidBodyDividedMeshShapeMgr::~RigidBodyDividedMeshShapeMgr() {
    for (auto*& body : mBoundaryBodies) {
        if (body)
            body->sub_7101223EC4();
        delete body;
    }
    for (auto& info : mHandles) {
        auto* resource = sead::DynamicCast<TeraMeshRigidBodyResource>(info.handle.getResource());
        auto* body = resource ? resource->getRigidBody() : nullptr;
        if (body && body->isAddedToWorld()) {
            resource = sead::DynamicCast<TeraMeshRigidBodyResource>(info.handle.getResource());
            body = resource ? resource->getRigidBody() : nullptr;
            body->removeFromWorldImmediately(nullptr);
        }
    }
    mHandles.freeBuffer();
    System::instance()->setRigidBodyDividedMeshShapeMgr(nullptr);
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
        if (ksys::aoc::Manager::instance())
            request.mAocFileDevice = ksys::aoc::Manager::instance()->getFileDeviceForTeraMesh(path);
        info->handle.requestLoad(path, &request, nullptr);
    }
    if (info->handle.isReadyOrNeedsParse())
        info->handle.parseResource(nullptr);
}

}  // namespace ksys::phys
