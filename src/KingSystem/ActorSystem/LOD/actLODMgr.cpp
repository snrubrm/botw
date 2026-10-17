#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <prim/seadMemUtil.h>
#include <heap/seadHeap.h>
#include <gfx/seadCamera.h>
#include "KingSystem/Camera/CameraMgr.h"
#include <gsys/gsysModel.h>

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(LODMgr)

LODMgr::~LODMgr() {
    if (_21b8)
        delete _21b8;
    _1838.freeBuffer();
}

void LODMgr::init(sead::Heap* heap) {
    const sead::Heap* const heap_arg = heap;
    _21b8 = new (heap, 8) Unk_71011086dc();
    _21b8->sub_7101108774(heap_arg);
    _1838.allocBuffer(512, heap, 8);
}

void LODMgr::initBeforeStageGenB() {
    _1028 = 0;
    _1830 = 0;
    _21a0 = 0;
    mSlotPools[0].count = 0;
    mSlotPools[0].index = 0;
    mSlotPools[1].count = 0;
    mSlotPools[1].index = 0;
    _1c80 = 0;
    _1878 = 0;
    _2110.fill(0);
}

// NON_MATCHING: the loads of the two camera vectors are grouped / scheduled differently
void LODMgr::sub_7101251B08(sead::Vector3f* pos) {
    if (!pos)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    sead::Vector3f dir;
    dir.setSub(camera->getAt(), camera->getPos());
    dir.normalize();
    *pos = camera->getPos();
    *pos += dir * 5.0f;
}

// 0x71012537e8 (placeholder name): the draw bit of a queued slot is cleared when its LodState is
// taken back into the pool. Each pool may take at most 5 - the slots the previous calc used.
// NON_MATCHING: clang reassociates the budget to `5 - used0 - used1` (the original adds the two used
// counts first) and turns the countdown into an incrementing counter.
void LODMgr::calc_x_0() {
    s32 budget = 5 - (mSlotPools[0].used + mSlotPools[1].used);

    if (mSlotPools[0].count != 0) {
        s32 n = mSlotPools[0].count > budget ? budget : mSlotPools[0].count;
        if (n < 2)
            n = 1;
        s32 i = n - 1;
        if (i >= 0) {
            do {
                const s32 index = mSlotPools[0].index % mSlotPools[0].count;
                mSlotPools[0].slots[u32(index) < 0x40 ? index : 0].state->mFlags8.reset(0x40);
                ++mSlotPools[0].index;
            } while (i-- != 0);
        } else {
            n = 0;
        }
        budget -= n;
        mSlotPools[0].taken = n;
    }

    if (mSlotPools[1].count != 0) {
        s32 n = mSlotPools[1].count > budget ? budget : mSlotPools[1].count;
        if (n < 2)
            n = 1;
        s32 i = n - 1;
        if (i >= 0) {
            do {
                const s32 index = mSlotPools[1].index % mSlotPools[1].count;
                mSlotPools[1].slots[u32(index) < 0x40 ? index : 0].state->mFlags8.reset(0x40);
                ++mSlotPools[1].index;
            } while (i-- != 0);
        } else {
            n = 0;
        }
        mSlotPools[1].taken = n;
    }
}

void LODMgr::requestDrawModels() {
    const s32 count = _1838.size();
    if (count < 1)
        return;
    for (s32 i = 0; i <= count - 1; ++i)
        _1838[i]->requestDraw();
}

}  // namespace ksys::act
