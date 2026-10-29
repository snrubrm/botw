#include "Game/gameVillagerMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/GameConfig.h"
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
    if (ksys::GameConfig::getInstance()->_3dc)
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

// 0x7100d5f80c (CSV VillagerMgr::x_4): releases the raycast request of `actor`'s villager entry and
// updates the actor's villager state through x_5. `a2` is unused.
// NON_MATCHING: the tail call moves the actor to x1 in the original, i.e. its x_5 takes an unused first
// argument; ours passes it in x0 (x_5's body never reads x0). Everything else is instruction-identical.
void VillagerMgr::x_4(ksys::act::Actor* actor, s32 a2) {
    if (!actor->mVillagerListNode.isLinked() ||
        (actor->isCalc() && actor->mStateFlags.isZero()))
        return;

    for (auto& entry : mEntries) {
        if (entry._0 == actor->getId()) {
            if (entry.mRayCast) {
                entry.mRayCast->release();
                entry.mRayCast = nullptr;
            }
            entry._0 = -1;
            break;
        }
    }

    x_5(actor);
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
