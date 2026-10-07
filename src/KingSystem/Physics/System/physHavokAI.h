#pragma once

#include <limits>
#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class NavMeshCharacter;
class Unk_7100f7e9f0;

// Placeholder name (vtable 0x7102372790; a second base with its own vtable at +0x10): base of the
// navmesh query requests that AI / horse code allocates from NavMeshQueryRequestPool's heap and
// hands to HavokAI::submitQuery / destroyQuery (e.g. the derived class with vtable 0x71024ed690).
// TODO: incomplete (virtuals: D1 0x71000e43e8, D0, 0x71000e4348 (clears _8), 0x71000e4350, a pure
// slot, 0x71000e43d0).
class Unk_7102372790 {
public:
    virtual ~Unk_7102372790();

    /* 0x08 */ bool _8;  // set when the request is queued
    /* 0x09 */ bool _9;  // set by destroyQuery before it is queued
    /* 0x0c */ sead::Vector3f _c;  // the result position (MotorcycleMgr::spawnMotorcycle_x; layout of the
                                   // derived query class not modelled)
    u8 _18[0x24 - 0x18];
    /* 0x24 */ s32 _24;
};

// Name from the CSV (NavMeshLoadMgr::a 0x7100f8a3b8 ... 0x7100f8bf64; lane1 s26: placeholder, only what callers use is declared;
// HavokAI::_48). The navmesh tile loader: tiles are requested by world position (x, z).
class NavMeshLoadMgr {
public:
    // 0x7100f8aca4 (CSV NavMeshLoadMgr::x_1; declared only): whether the tile of `pos` is covered (false when the manager is
    // disabled or has no tiles).
    bool x_1(const sead::Vector3f* pos);
    // 0x7100f8b334 (declared only; placeholder name): requests loading the tile of `pos`.
    void sub_7100F8B334(const sead::Vector3f* pos);
    // 0x7100f8b444 (CSV NavMeshLoadMgr::x_2; declared only): releases the requested tile.
    void x_2();
};

// Placeholder name; inline-only in the original (evidence: the same lock-free push loop is inlined into
// NavMeshQueryRequestPool::sub_71012A9EE8 / sub_71012A9F68 / sub_71012AA000 / sub_71012AA080 and HavokAI::sub_7100F82BCC).
// A ring of `mCapacity` (a power of two) item pointers with an atomic tail and a head, 0x18 bytes: the pool has six of
// them (0x108, 0x120, 0x138, 0x150, 0x168, 0x180).
template <typename T>
struct Unk_RequestQueue {
    // Appends `item` unless the queue is full (or `item` is null).
    bool push(T* item) {
        if (!item)
            return false;
        s32 tail = mTail.load();
        while (tail - mHead < mCapacity) {
            if (mTail.compareExchange(tail, tail + 1)) {
                mBuffer[tail & (mCapacity - 1)] = item;
                return true;
            }
            tail = mTail.load();
        }
        return false;
    }

    // Replaces the entries equal to `item` that are still queued by -1.
    void remove(T* item) {
        for (u32 i = mHead; i < u32(mTail.load()); ++i) {
            const s32 index = i & (mCapacity - 1);
            if (mBuffer[index] == item)
                mBuffer[index] = reinterpret_cast<T*>(-1);
        }
    }

    /* 0x00 */ s32 mCapacity;
    /* 0x08 */ T** mBuffer;
    /* 0x10 */ sead::Atomic<s32> mTail;
    /* 0x14 */ s32 mHead;
};
KSYS_CHECK_SIZE_NX150(Unk_RequestQueue<void>, 0x18);

// Name from the CSV (NavMeshQueryRequestPool::ctor 0x71012a8ffc, heap name
// "NavMeshQueryRequestPool"). Owns the request heap and lock-free request queues.
// TODO: incomplete.
class NavMeshQueryRequestPool {
public:
    // 0x71012a9ee8: sets query->_9 and pushes it to the queue at +0x180.
    void sub_71012A9EE8(Unk_7102372790* query);
    // 0x71012a9f68: pushes the query to the queue at +0x180; false if it is null or the queue is full.
    bool sub_71012A9F68(Unk_7102372790* query);
    // 0x71012aa000 (declared only): sets query->_9 = 1.
    void sub_71012AA000(Unk_7102372790* query);

    // 0x71012aa080 (same as sub_71012A9F68), 0x71012aa118 / 0x71012aa1f0: remove `query` / the character
    // from the queues (under the lock at +8 / +0x48).
    bool sub_71012AA080(Unk_7102372790* query);
    void sub_71012AA118(Unk_7102372790* query);
    void sub_71012AA1F0(NavMeshCharacter* nav);

    /* 0x000 */ u8 _0[8];
    /* 0x008 */ sead::CriticalSection _8;
    /* 0x048 */ sead::CriticalSection _48;
    /* 0x088 */ u8 _88[0x108 - 0x88];
    /* 0x108 */ Unk_RequestQueue<Unk_7102372790> _108;
    /* 0x120 */ Unk_RequestQueue<Unk_7102372790> _120;
    /* 0x138 */ Unk_RequestQueue<NavMeshCharacter> _138;  // pushed by HavokAI::sub_7100F82BCC
    /* 0x150 */ u8 _150[0x180 - 0x150];
    /* 0x180 */ Unk_RequestQueue<Unk_7102372790> _180;
    /* 0x198 */ Unk_7102372790* _198;
};

// Name from the CSV (HavokAI::createInstance 0x7100f80b20, init 0x7100f80f38, ...). A polymorphic sead
// singleton (vtable 0x71024f6e88: D1 0x7100f80c60, D0 0x7100f80eb8; size 0x178; instance pointer at
// 0x710260de68). Members known from createInstance / init / the dtor: NavMeshSystemThread* at +0x38,
// NavMeshQueryRequestPool* at +0x40, a CriticalSection at +0x50, two sead::Events at +0x90 / +0xc8,
// three offset lists at +0x100 / +0x118 / +0x130. Only what callers use is declared so far.
class HavokAI {
    SEAD_SINGLETON_DISPOSER(HavokAI)
    HavokAI();
    virtual ~HavokAI();

public:
    // Placeholder: result of sub_7100F86174 (callers build it on the stack: twelve NaN floats and a
    // zeroed u16). _24 is the resulting point.
    struct Unk1 {
        sead::Vector3f _0{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
        sead::Vector3f _c{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
        sead::Vector3f _18{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
        sead::Vector3f _24{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
        u16 _30 = 0;
    };

    // 0x7100f86174 (not decompiled): a navmesh query from `from` towards `to` (`a4`: a height
    // tolerance); true if it hit.
    bool sub_7100F86174(const sead::Vector3f& from, const sead::Vector3f& to, Unk1* result, f32 a4);

    // 0x7100f87ed0 (CSV HavokAI::__auto3, declaration only): the HavokAI counterpart of
    // NavMeshCharacter::sub_7100F76078 (closest navmesh point to `to`, written to `out`).
    Unk_7100f7e9f0 sub_7100F87ED0(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);

    // 0x7100f87a80 (declaration only): navmesh query between `from` and `to` (PriestBossMove::m35 passes the
    // point raised and lowered by 1), writing the hit point to `out`.
    Unk_7100f7e9f0 sub_7100F87A80(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to);

    // 0x7100f88b1c (unnamed in the CSV; not decompiled): NavMeshCharacter::sub_7100F76078 forwards here.
    Unk_7100f7e9f0 sub_7100F88B1C(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to,
                                  f32 a3);

    // 0x7100f82bcc (CSV HavokAI::__auto2): registers a navmesh character: clears flag 2 / sets flag 1 of
    // its `_220`, stores this in its `_20` and queues it. Callers run it when `nav->_18` is null.
    void sub_7100F82BCC(NavMeshCharacter* nav);

    // 0x7100f82dd8 (not decompiled): counterpart of sub_7100F82BCC (called with the same guard).
    void sub_7100F82DD8(NavMeshCharacter* nav);

    // 0x7100f88fd0 (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F760F0 forwards here.
    Unk_7100f7e9f0 sub_7100F88FD0(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to);

    // 0x7100f87594 (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F76168 / sub_7100F761C8 forward here
    // (`pos` may be null; `radius` is the character's `_2a8 * _2ac`).
    bool sub_7100F87594(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius, f32 value, bool flag,
                        void* out);

    // 0x7100f83a9c (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F75AF0 forwards its query here.
    void sub_7100F83A9C(Unk_7102372790* query);

    // 0x7100f83a94 (CSV HavokAI::__auto4): hands the query back to the pool (NavMeshCharacter::finalize).
    void sub_7100F83A94(Unk_7102372790* query);

    // 0x7100f83a84 / 0x7100f83a8c (CSV names).
    void destroyQuery(Unk_7102372790* query);
    bool submitQuery(Unk_7102372790* query);

    u8 _28[0x40 - 0x28];
    NavMeshQueryRequestPool* _40;
    NavMeshLoadMgr* _48;
    u8 _50[0x178 - 0x50];
};
KSYS_CHECK_SIZE_NX150(HavokAI, 0x178);

}  // namespace ksys::phys
