#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <prim/seadMemUtil.h>
#include <heap/seadHeap.h>
#include <gfx/seadCamera.h>
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(LODMgr)

LODMgr::~LODMgr() {
    if (_21b8)
        delete _21b8;
    _1838.freeBuffer();
}

void LODMgr::sub_7101254394(sead::Vector3f* center, f32* radius, f32* distance,
                           Actor* actor, const sead::Vector3f* camera) {
    if (!center || !radius || !distance || !actor)
        return;
    const auto* state = actor->getLodState();
    if (!state)
        return;
    if (actor->m33()) {
        actor->m34(center, radius);
    } else {
        actor->getMtx().getTranslation(*center);
        const auto& bounds = actor->getAabb();
        *radius = (bounds.getMin() - bounds.getMax()).length() * 0.5f;
        if ((actor->mVillagerListNode.next() || actor->mVillagerListNode.prev()) &&
            actor->isCalc() && actor->mStateFlags.isZero())
            *radius += 0.05f;
        *center += (bounds.getMin() + bounds.getMax()) * 0.5f;
    }
    const f32 inv_scale = 1.0f / state->mDistanceScale;
    const f32 x = inv_scale * (camera->x - center->x);
    const f32 z = inv_scale * (camera->z - center->z);
    *distance = x * x + z * z;
}

// NON_MATCHING: the state-range predicate and flag branches are folded and scheduled differently.
void LODMgr::sub_7101254734(LodState* state, const sead::Vector3f& center, f32 distance) {
    if (state->mFlags10.isOnBit(6) || state->mFlags14.isOffBit(6))
        return;
    auto* actor = state->mActor;
    if (actor->_718 > 0.0f || evt::Manager::instance()->_1d2f8 == 1 ||
        (actor->getActorFlags2().getDirect() & 0x800000))
        return;
    if (state->mFlags14.isOnBit(16) && actor->getLife()) {
        const auto* life = actor->getLife();
        if (life && *life == 0) {
            ++_2194;
            return;
        }
    }
    if (state->_1c != 2 && (state->_1c != 3 || actor->checkFlag(Actor::ActorFlag::_39)) &&
        u32(state->_1c - 4) > 1) {
        if (state->_1c != 1 || state->mFlags14.isOffBit(15) ||
            (state->mFlags14.isOnBit(22) && !(sUnk_71026531A8 & 0x20000)) ||
            (state->mFlags14.isOnBit(23) && distance <= 900.0f))
            return;
        state->mFlags8.setBit(6);
        return;
    }
    if (state->mFlags14.isOffBit(15) && !actor->checkFlag(Actor::ActorFlag::_39) &&
        state->mFlags26.isOffBit(2)) {
        if (actor->m128() && actor->m128()->m2())
            return;
        if (actor->getPhysics() && actor->getPhysics()->sub_7100FBB420())
            return;
    }
    if (state->_74 > distance)
        return;
    state->mFlags8.setBit(6);
    for (s32 i = 0; i < _1878; ++i) {
        const f32 x = _1848[i].x - center.x;
        const f32 z = _1848[i].z - center.z;
        if (x * x + z * z < 225.0f)
            state->mFlags8.resetBit(6);
    }
}

// NON_MATCHING: state stores and flag tests are folded differently; global flag access also differs.
bool LODMgr::sub_7101254544(LodState* state, const sead::Vector3f& center, f32 radius,
                            f32 distance) {
    const bool inside = mFrustum.isInside(center, radius);
    const f32 near_distance = state->_68 * 10.0f + radius;
    auto* actor = state->mActor;
    state->mFlags8.changeBit(29, inside);
    const auto* object = actor->getMapObject();
    state->mFlags8.resetBit(21);
    if (near_distance * near_distance > distance) {
        state->_1c = 0;
        return state->mFlags8.isOnBit(29);
    }
    if (state->mFlags8.isOffBit(29)) {
        state->_1c = object && state->mDispDistance * state->mDispDistance < distance ? 5 : 2;
        return state->mFlags8.isOnBit(29);
    }
    if (object) {
        if (state->mFlags26.isOffBit(4)) {
            const f32 limit = state->mDispDistance + state->mDispDistance;
            if (limit * limit < distance) {
                state->_1c = 3;
                return state->mFlags8.isOnBit(29);
            }
        } else if (mFrustum.get_f4() * std::sqrt(distance) >= state->_78) {
            state->_1c = 3;
            return state->mFlags8.isOnBit(29);
        }
    }
    if (mNearFrustum.isInside(center, radius) && (sUnk_71026531A8 & 0x100) &&
        state->mFlags14.isOnBit(25) && state->mOcclusionQueryCylinder && actor->getModel() &&
        !actor->m39() && (state->mActor->mVillagerListNode.next() || 900.0f < distance ||
                         state->mActor->mVillagerListNode.prev())) {
        state->mFlags8.setBit(21);
        if (state->sub_71012511FC())
            return state->mFlags8.isOnBit(29);
        if (state->sub_71012511C8()) {
            state->mFlags8.setBit(28);
            state->_1c = 4;
            return state->mFlags8.isOnBit(29);
        }
        state->mFlags8.resetBit(28);
    }
    state->_1c = 1;
    return state->mFlags8.isOnBit(29);
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
