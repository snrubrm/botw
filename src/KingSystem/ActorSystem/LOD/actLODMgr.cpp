#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <prim/seadMemUtil.h>
#include <heap/seadHeap.h>
#include <gfx/seadCamera.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/XLink/xlinkXLink.h"
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

KSYS_VISIBILITY_HIDDEN u32 sUnk_71026531A8;

void LODMgr::postCalc() {
    sub_7101254984(this);
}

void LODMgr::calc_x_1() {
    for (s32 i = 0; i < _1830; ++i) {
        LodState* state = _1030[u32(i) < 0x100 ? i : 0];
        Actor* actor = state->mActor;
        Actor* other = actor->m31();
        if (!other) {
            state->sub_7101251240();
        } else {
            LodState* other_state;
            do {
                other_state = other->getLodState();
                other = other->m31();
            } while (other);

            if (!other_state) {
                state->sub_7101251240();
            } else {
                state->mFlags8.change(0x1, other_state->mFlags8.isOn(0x1));
                state->mFlags8.change(0x2, other_state->mFlags8.isOn(0x2));
                state->mFlags8.change(0x4, other_state->mFlags8.isOn(0x4));
                state->mFlags8.change(0x10, other_state->mFlags8.isOn(0x10));
                state->mFlags8.change(0x8, other_state->mFlags8.isOn(0x8));
                state->mFlags8.change(0x40, other_state->mFlags8.isOn(0x40));
                state->mFlags8.change(0x100, other_state->mFlags8.isOn(0x100));
                state->mFlags8.change(0x200, other_state->mFlags8.isOn(0x200));
                state->mFlags8.change(0x1000, other_state->mFlags8.isOn(0x1000));
                state->mFlags8.change(0x400, other_state->mFlags8.isOn(0x400));
                state->mFlags8.change(0x80, other_state->mFlags8.isOn(0x80));
                state->sub_7101251280(other_state->_28);
                state->_1c = other_state->_1c;
                state->_25 = other_state->_24;
            }
        }

        sub_71012540AC(state);
        if (state->mFlags14.isOn(0x2) && state->mFlags8.isOn(0x2))
            ++_2174;
    }
}

// NON_MATCHING: 4 bytes larger (an unused x23 save) and block layout / register allocation only;
// the original also tests _25 bit 7 with ldrb + tbnz instead of our sign-extended load.
void LODMgr::sub_71012540AC(LodState* state) {
    if (sUnk_71026531A8 & 0x20)
        state->mFlags8.set(0x100);

    if (state->mFlags8.isOn(0x4000)) {
        state->mFlags8.reset(0x1640);
        ++_21a8;
    }

    if (!state->mFlags14.isOn(0x1000))
        state->mFlags8.reset(0x1000);
    if (!state->mFlags14.isOn(0x200))
        state->mFlags8.reset(0x200);

    if (!(sUnk_71026531A8 & 0x2000) && state->mActor->getChemicalContainer() &&
        !state->mActor->getChemicalContainer()->x_0()) {
        state->mFlags8.reset(0x40);
        ++_219c;
    }

    Actor* actor = state->mActor;
    if (actor->getActorFlags2().isOn(Actor::ActorFlag2::_40))
        state->_60 = 0;

    if (!(sUnk_71026531A8 & 0x4000) && state->_60 < state->mDisableCalcSkipFrame) {
        state->mFlags8.reset(0x40);
        ++_2198;
    }

    const u32 flags18 = state->mFlags18.getDirect();
    if (flags18 & 0x40000000) {
        const bool on = (flags18 & 0x40) != 0;
        u64 flags = (state->mFlags8.getDirect() & ~u64(0x1f)) | (flags18 & 0x1f);
        flags = on ? (flags | 0x40) : (flags & ~u64(0x40));
        flags = on ? (flags | 0x80) : (flags & ~u64(0x80));
        state->mFlags8.setDirect(flags);
    }

    if (!state->mFlags8.isOn(0x40))
        ++_2178;
    if (!state->mFlags8.isOn(0x100))
        ++_217c;
    if (!state->mFlags8.isOn(0x200))
        ++_2180;
    if (!state->mFlags8.isOn(0x400))
        ++_2184;
    if (state->mFlags8.isOn(0x1000))
        ++_2190;
    if (state->mFlags14.isOn(0x1) && state->mFlags8.isOn(0x1))
        ++_2170;

    u16 job_mask = actor->mSpecialJobTypesMask.getDirect();
    if (!(sUnk_71026531A8 & 0x40) && state->mFlags8.isOn(0x40) &&
        ((!actor->getCharacterController() && !actor->getMainBody()) ||
         (state->_25.getDirect() & 0x80u) != 0)) {
        job_mask |= 2;
    } else {
        job_mask &= ~u16(2);
    }
    actor->mSpecialJobTypesMask.setDirect(job_mask);

    ksys::xlink::XLink* xlink = actor->getXLink();
    if (!xlink)
        return;
    if (!(sUnk_71026531A8 & 0x80) && state->mFlags14.isOn(0x40) && !actor->get1a0() &&
        (!actor->getMapObject() ||
         !actor->getMapObject()->getFlags0().isOn(map::Object::Flag0::_20000)) &&
        !actor->getActorFlags2().isOn(Actor::ActorFlag2::_100) &&
        (state->_1c == 3 || state->_1c == 5) && state->mFlags14.isOn(0x1000)) {
        xlink->sub_7101230E68(true);
        actor->mSpecialJobTypesMask.set(0x10);
        ++_218c;
        return;
    }
    xlink->sub_7101230E68(false);
    actor->mSpecialJobTypesMask.reset(0x10);
}

void LODMgr::requestDrawModels() {
    const s32 count = _1838.size();
    if (count < 1)
        return;
    for (s32 i = 0; i <= count - 1; ++i)
        _1838[i]->requestDraw();
}

}  // namespace ksys::act
