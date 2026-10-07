#include "Game/gameVillagerMgr.h"
#include "KingSystem/Framework/GameConfig.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking {

VillagerMgr::VillagerMgr(const sead::Vector3f& pos) : mPos(pos) {
    mActors.initOffset(0x388);
}

// NON_MATCHING: the original spills an unknown bit-index enum before setting bit 5; the natural mask is folded here.
void VillagerMgr::init(sead::Heap* heap) {
    mEntries.tryAllocBuffer(10, heap);
    for (auto& entry : mEntries) {
        if (entry.mRayCast) {
            entry.mRayCast->release();
            entry.mRayCast = nullptr;
        }
        entry._0 = -1;
    }
    mFlags = 0;
    if (GameConfig::getInstance()->_3dc)
        mFlags |= 0x20;
    using ksys::phys::ContactLayer;
    mLayerMasks.addLayer(ContactLayer::EntityAirWall);
    mLayerMasks.addLayer(ContactLayer::EntityGround);
    mLayerMasks.addLayer(ContactLayer::EntityGroundObject);
    mLayerMasks.addLayer(ContactLayer::EntityGroundSmooth);
    mLayerMasks.addLayer(ContactLayer::EntityGroundRough);
    mLayerMasks.addLayer(ContactLayer::EntityNPC);
    mLayerMasks.addLayer(ContactLayer::EntityNPC_NoHitPlayer);
    mLayerMasks.addLayer(ContactLayer::EntityObject);
    mLayerMasks.addLayer(ContactLayer::EntityPlayer);
    mLayerMasks.addLayer(ContactLayer::EntityRagdoll);
    mLayerMasks.addLayer(ContactLayer::EntityTree);
    mLayerMasks.removeLayer(ContactLayer::EntityWater);
}

VillagerMgr::~VillagerMgr() {
    for (auto& entry : mEntries) {
        if (entry.mRayCast) {
            entry.mRayCast->release();
            entry.mRayCast = nullptr;
        }
    }
    mEntries.freeBuffer();
}

}  // namespace uking
