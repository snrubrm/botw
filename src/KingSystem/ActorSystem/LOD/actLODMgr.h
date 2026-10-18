#pragma once

#include <container/seadObjList.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <cull/aglViewFrustumCulling.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys::act {

class LodState;
class Actor;

// 0x71026531a8 (GOT 0x71025a2d40): the LOD debug / enable flag word. Only the LOD manager code
// reads it; bit 5 / 6 / 13 / 14 gate the state updates and the debug counters.
extern u32 sUnk_71026531A8;

// Placeholder name (ctor 0x71011086dc, dtor 0x71011086f0, init 0x7101108774; size 0x30): created by
// LODMgr::init (LODMgr + 0x21b8). A sead::ObjList of 0x20-byte entries: the dtor is ObjList::freeBuffer and
// the init allocates the node pool (nodes of 0x30 bytes, list node at +0x20). Defined in the terrain TU
// (teraResourceNode.cpp).
struct Unk_71011086dcEntry {
    u8 _0[0x20];
};

class Unk_71011086dc : public sead::ObjList<Unk_71011086dcEntry> {
public:
    Unk_71011086dc();
    ~Unk_71011086dc();
    // 0x7101108774: allocates room for Terrain::_3d0 * sqrt(2) + 1 entries.
    void sub_7101108774(const sead::Heap* const& heap);
};
static_assert(sizeof(Unk_71011086dc) == 0x30);

// Name from the CSV (LODMgr::createInstance 0x710125184c, instance pointer 0x71026531b8; size 0x2a60;
// TU 0x7101250ed8 - 0x7101252xxx together with LodState's later methods). Only a few members are
// declared so far; the constructor (inlined in createInstance) is not decompiled.
class LODMgr {
    SEAD_SINGLETON_DISPOSER(LODMgr)
    LODMgr();
    virtual ~LODMgr();

public:
    void init(sead::Heap* heap);
    void initBeforeStageGenB();
    // 0x7101251b08 (CSV LODMgr::__auto3): `pos` + 5 along the look direction of the look-at camera.
    void sub_7101251B08(sead::Vector3f* pos);
    // 0x7101254328 (CSV name): requests a draw for every model in _1838.
    void requestDrawModels();
    // 0x71012537e8 (CSV LODMgr::calc_x_0; placeholder name): takes back the queued slots of both
    // pools, at most 5 minus the slots the previous calc used, and clears their draw bit.
    void calc_x_0();
    void calc_x(const sead::Vector3f* camera);
    // 0x7101253b20 (CSV LODMgr::calc_x_1): copies the flags of each state's linked actor's LodState
    // into the state and updates the neighbours.
    void calc_x_1();
    // 0x71012540ac (unnamed in the CSV; placeholder name): applies the manager flags and the actor's
    // chemical / xlink state to one LodState, then updates the debug counters.
    void sub_71012540AC(LodState* state);
    // 0x7101254980 (4-byte tail call): forwards to the still undecompiled helper 0x7101254984.
    void postCalc();
    // 0x7101254394: actor bounding sphere and scaled horizontal distance.
    static void sub_7101254394(sead::Vector3f* center, f32* radius, f32* distance,
                               Actor* actor, const sead::Vector3f* camera);
    bool sub_7101254544(LodState* state, const sead::Vector3f& center, f32 radius, f32 distance);
    void sub_7101254734(LodState* state, const sead::Vector3f& center, f32 distance);

    struct Slot {
        LodState* state;
        f32 distance;
        u32 _c;
    };
    static_assert(sizeof(Slot) == 0x10);
    // 0x71012538ec sorts these slots, reads count at +0x400 and advances
    // a separate round-robin index at +0x404.
    struct OcclusionPool {
        s32 sub_71012538EC(u32 flags);
        sead::SafeArray<Slot, 0x40> slots;
        s32 count;
        s32 index;
    };
    static_assert(sizeof(OcclusionPool) == 0x408);
    /* 0x0028 */ sead::SafeArray<LodState*, 0x200> _28;  // the LodStates calc() walks
    /* 0x1028 */ s32 _1028;
    /* 0x102c */ u8 _102c[4];
    /* 0x1030 */ LodState* _1030[0x100];  // the LodStates calc_x_1() walks (index masked to 8 bits)
    /* 0x1830 */ s32 _1830;
    /* 0x1838 */ sead::PtrArray<gsys::Model> _1838;
    /* 0x1848 */ sead::SafeArray<sead::Vector3f, 4> _1848;
    /* 0x1878 */ s32 _1878;
    /* 0x187c */ u8 _187c[4];
    /* 0x1880 */ OcclusionPool mOcclusionPool;
    /* 0x1c88 */ agl::cull::ViewFrustumCulling mFrustum;
    /* 0x1ec0 */ agl::cull::ViewFrustumCulling mNearFrustum;
    /* 0x20f8 */ sead::Vector3f mCameraDirection;
    u8 _2104[0x2110 - 0x2104];
    /* 0x2110 */ sead::SafeArray<u32, 24> _2110;
    // The LOD debug counters that calc_x / calc_x_1 / the per-state helper increment.
    /* 0x2170 */ s32 _2170;
    /* 0x2174 */ s32 _2174;
    /* 0x2178 */ s32 _2178;
    /* 0x217c */ s32 _217c;
    /* 0x2180 */ s32 _2180;
    /* 0x2184 */ s32 _2184;
    /* 0x2188 */ u32 _2188;  // not reset by calc_x
    /* 0x218c */ s32 _218c;
    /* 0x2190 */ s32 _2190;
    /* 0x2194 */ s32 _2194;
    /* 0x2198 */ s32 _2198;
    /* 0x219c */ s32 _219c;
    /* 0x21a0 */ s32 _21a0;
    /* 0x21a4 */ s32 _21a4;
    /* 0x21a8 */ s32 _21a8;
    /* 0x21ac */ u8 _21ac[0x21b8 - 0x21ac];
    /* 0x21b8 */ Unk_71011086dc* _21b8;
    /* 0x21c0 */ sead::Vector3f _21c0;
    u8 _21cc[0x21dc - 0x21cc];
    // calc_x suppresses distance-based requests when this byte is set.
    bool _21dc;
    u8 _21dd[0x2200 - 0x21dd];
    // calc computes this scale from the projection field of view.
    f32 _2200;
    u8 _2204[4];

    // The two render-slot pools (0x410 bytes each, one per LOD group). calc_x queues a LodState with its
    // distance in 0x710125316c; calc_x_0 takes the queued slots back and clears their bit 6.
    struct SlotPool {
        // Slots the previous calc used (0x2208 / 0x2618).
        s32 used;
        // Slots calc_x_0 took (0x220c / 0x261c).
        s32 taken;
        Slot slots[0x40];
        // Number of queued slots (0x2610 / 0x2a20).
        s32 count;
        // Ring index into `slots` (0x2614 / 0x2a24).
        s32 index;
    };
    static_assert(sizeof(SlotPool) == 0x410);
    /* 0x2208 */ SlotPool mSlotPools[2];
    /* 0x2a28 */ u8 _2a28[0x2a60 - 0x2a28];
};
KSYS_CHECK_SIZE_NX150(LODMgr, 0x2a60);

// 0x7101254984 (1012 B, still undecompiled): the body behind LODMgr::postCalc.
void sub_7101254984(LODMgr* self);

}  // namespace ksys::act
