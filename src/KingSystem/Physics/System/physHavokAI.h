#pragma once

#include <limits>
#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <math/seadBoundBox.h>
#include <thread/seadEvent.h>
#include "KingSystem/Utils/Container/LockFreeQueue.h"
#include <thread/seadCriticalSection.h>
#include <thread/seadThread.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

// Game/AI/aiUnk_NavMeshCallback.h
class Unk_NavMeshCallback;

namespace ksys::res {
class Handle;
}

namespace ksys::phys {

class HavokAI;
class NavMeshCharacter;
class Unk_7100f7e9f0;

// NavMeshSystemThread (ctor 0x7100f89514, D0 0x7100f897a8, calc_ 0x7100f8972c,
// vtable 0x71024f70b0): HavokAI's navmesh worker thread (HavokAI::_38).
// TODO: incomplete (ctor args, calc_ body, the sub-object with its own vtable at +0x30,
// members at +0x100/+0x108/+0x10c).
class NavMeshSystemThread : public sead::Thread {
public:
    // 0x7100f8972c (declaration only).
    void calc_(sead::MessageQueue::Element msg) override;

    // 0x7100f895fc (placeholder name): unless stopped (_10c), accumulates `dt` in _108 and sends the 'step' message.
    void sub_7100F895FC(f32 dt);

    u8 _pad[0x100 - sizeof(sead::Thread)];
    /* 0x100 */ void* _100;
    /* 0x108 */ f32 _108;
    /* 0x10c */ bool _10c;
};

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
    NavMeshLoadMgr();
    virtual ~NavMeshLoadMgr();
    // 0x7100f898e4: releases the loaded Havok tile resources (declared only).
    void sub_7100F898E4();
    // 2026-10-07: createResources constructs ten resource handles at 0x60-byte
    // intervals; sub_7100F8ADC4 walks the same array and sub_7100F8AF0C checks status58.
    struct TileHandle : public res::Handle {
        /* 0x50 */ s32 _50;
        /* 0x54 */ s32 _54;
        /* 0x58 */ u8 _58;
        /* 0x59 */ u8 _59[7];
        bool sub_7100F8AF0C();
    };
    KSYS_CHECK_SIZE_NX150(TileHandle, 0x60);
    // 0x7100f89f4c (CSV NavMeshLoadMgr::x; declared only; 1132 B): called with Vector3f::zero by the dungeon stages' preCalc.
    void x(const sead::Vector3f* pos);
    // 0x7100f8aca4 (CSV NavMeshLoadMgr::x_1; declared only): whether the tile of `pos` is covered (false when the manager is
    // disabled or has no tiles).
    bool x_1(const sead::Vector3f* pos);
    // 2026-10-07: HavokAI::init constructs this manager at +0x48; the query
    // returns a normalized boolean after checking the requested tile resource.
    bool sub_7100F8ADC4(const sead::Vector3f* pos);
    // 0x7100f8aba0: position is within one tile of the currently selected tile.
    bool x_0(const sead::Vector3f* pos);
    // 0x7100f8b334 (declared only; placeholder name): requests loading the tile of `pos`.
    void sub_7100F8B334(const sead::Vector3f* pos);
    // 0x7100f8b444 (CSV NavMeshLoadMgr::x_2; declared only): releases the requested tile.
    void x_2();
    // 0x7100f8a670 (CSV NavMeshLoadMgr::x_3; declared only): called with the same handle twice.
    void x_3(TileHandle* a, TileHandle* b);

    /* 0x008 */ u32 _8;
    // 0x7100f8a3b8 (CSV NavMeshLoadMgr::a; declared only): requests the tile of the handle.
    void a(TileHandle* handle);
    /* 0x010 */ TileHandle* _10;
    /* 0x018 */ sead::FixedSafeString<256> _18;
    /* 0x130 */ sead::CriticalSection _130;
    // 2026-10-07: ctor 0x7100f89800 loads Vector2i::zero for the first three pairs;
    // zero constant 0x7101e9fee8 was recovered by libwork (sead 258c4224).
    /* 0x170 */ sead::Vector2i _170;  // origin (x / z)
    /* 0x178 */ sead::Vector2i _178;  // tile size (x / z)
    /* 0x180 */ sead::Vector2i _180;  // tile counts (x / z)
    /* 0x188 */ sead::Vector2i _188;  // current tile (x / z)
    /* 0x190 */ bool _190;  // disabled
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

// Placeholder (the 0xb0-byte entries of InstanceSet::_100, the same layout as InstanceSet::Unk2): HavokAI queues
// them for adding / removing (0x7100f8305c, 0x7100f83118, 0x7100f833a8). `_a0` is the HavokAI that should handle
// the next request (exchanged with ldxr/stxr, compared against `this | 1`), `_a8` request flags (ldxr/stxr
// and / orr in those functions: sead::Atomic).
struct NavMeshObjMaybe {
    enum class Flag : u32 {
        _1 = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
        _10 = 1 << 4,
        _20 = 1 << 5,
        _40 = 1 << 6,
    };

    /* 0x00 */ u8 _0[0x98];
    /* 0x98 */ HavokAI* _98;  // the HavokAI it was added to
    /* 0xa0 */ sead::Atomic<HavokAI*> _a0;
    /* 0xa8 */ sead::TypedBitFlag<Flag, sead::Atomic<u32>> _a8;
};
KSYS_CHECK_SIZE_NX150(NavMeshObjMaybe, 0xb0);

// Placeholder (the object 0x7100f8b518 / 0x7100f8b538 pass to HavokAI 0x7100f83580 / 0x7100f8363c / 0x7100f83790):
// same request scheme as NavMeshObjMaybe with the HavokAI at +0x70, the pending one at +0x78 and the flags at +0x80.
struct NavMeshObj2Maybe {
    /* 0x00 */ u8 _0[0x70];
    /* 0x70 */ HavokAI* _70;
    /* 0x78 */ sead::Atomic<HavokAI*> _78;
    /* 0x80 */ sead::Atomic<u32> _80;
};

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
    // 0x71012aa270 / 0x71012aa2f0 (placeholder names): remove `obj` from the queue at +0x150 / +0x168.
    void sub_71012AA270(NavMeshObjMaybe* obj);
    void sub_71012AA2F0(NavMeshObj2Maybe* obj);

    /* 0x000 */ u8 _0[8];
    /* 0x008 */ sead::CriticalSection _8;
    /* 0x048 */ sead::CriticalSection _48;
    /* 0x088 */ sead::CriticalSection _88;  // guards _150 (0x71012aa270)
    /* 0x0c8 */ sead::CriticalSection _c8;  // guards _168 (0x71012aa2f0)
    /* 0x108 */ Unk_RequestQueue<Unk_7102372790> _108;
    /* 0x120 */ Unk_RequestQueue<Unk_7102372790> _120;
    /* 0x138 */ util::LockFreeQueue<NavMeshCharacter> _138;  // pushed by HavokAI::sub_7100F82BCC
    // The push loop of 0x7100f8305c etc. matches util::LockFreeQueue (same 0x18-byte layout as Unk_RequestQueue).
    /* 0x150 */ util::LockFreeQueue<NavMeshObjMaybe> _150;
    /* 0x168 */ util::LockFreeQueue<NavMeshObj2Maybe> _168;
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

    // 0x7100f8305c / 0x7100f83118 / 0x7100f833a8 (placeholder names): request bit 0 (clearing bit 1) / bit 2 /
    // bit 1 (clearing bit 0) for `obj` and queue it in the pool unless another HavokAI has it pending.
    void sub_7100F8305C(NavMeshObjMaybe* obj);
    void sub_7100F83118(NavMeshObjMaybe* obj);
    void sub_7100F833A8(NavMeshObjMaybe* obj);
    // 0x7100f831c0 / 0x7100f832b4 (placeholder names): set flag 8 / 0x20 and clear 0x10 / 0x40 (or the other way
    // round when `on` is false), then queue like sub_7100F8305C.
    void sub_7100F831C0(NavMeshObjMaybe* obj, bool on);
    void sub_7100F832B4(NavMeshObjMaybe* obj, bool on);
    // 0x7100f83580 / 0x7100f8363c (placeholder names): the same for NavMeshObj2Maybe (bit 0 / bit 2).
    void sub_7100F83580(NavMeshObj2Maybe* obj);
    void sub_7100F8363C(NavMeshObj2Maybe* obj);

    // 0x7100f82c88 (placeholder name): resets the character's path state (inlineReset) and queues it with bit 1
    // (clearing bit 0), like sub_7100F82BCC.
    void sub_7100F82C88(NavMeshCharacter* nav);

    // 0x7100f82dd8 (not decompiled): counterpart of sub_7100F82BCC (called with the same guard).
    void sub_7100F82DD8(NavMeshCharacter* nav);

    // 0x7100f8184c (CSV name): _38->sub_7100F895FC(dt).
    void sendStepMessageToNavMeshSysThread(f32 dt);
    // 0x7100f8185c (placeholder name): clears the thread's stop flag (_38->_10c).
    void sub_7100F8185C();

    // 0x7100f8183c: starts the navmesh system thread (_38->start()).
    bool startNavMeshSystemThread();

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

    // inline-only in the original; name is a guess. A shared lock: up to 0x100 holders, the event is reset by the first
    // and signalled when the last one leaves. The same acquire / release sequence is inlined into 0x7100f857f4,
    // 0x7100f854c4 and 0x7100f8565c (for _90 and _c8).
    struct SharedLock {
        bool tryLock() {
            while (true) {
                const u32 count = mCount.load();
                if (count > 0xff)
                    return false;
                if (!mCount.compareExchange(count, count + 1))
                    continue;
                if (count == 0)
                    mEvent.resetSignal();
                return true;
            }
        }

        void unlock() {
            if (mCount.decrement() == 1)
                mEvent.setSignal();
        }

        sead::Event mEvent;
        sead::Atomic<u32> mCount;
    };

    // 0x7100f85eb8 (700 B; declared only; was Unk_710260de68::sub_7100F85EB8): a line query from `from` to `to`
    // that answers whether something is in the way.
    bool sub_7100F85EB8(f32 radius, const sead::Vector3f* from, const sead::Vector3f* to, void* unused);

    // 0x7100f857f4 (placeholder name): visits the nav mesh nodes inside `aabb` with `callback` (0x7100f854c4 under _90, or 0x7100f8565c under _c8 if _90
    // is full). The callback is a caller-defined object (e.g. vtable 0x71023e7188).
    void sub_7100F857F4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);
    // 0x7100f854c4 / 0x7100f8565c (declared only).
    void sub_7100F854C4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);
    void sub_7100F8565C(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);

    u8 _28[0x38 - 0x28];
    NavMeshSystemThread* _38;
    NavMeshQueryRequestPool* _40;
    NavMeshLoadMgr* _48;
    /* 0x50 */ sead::CriticalSection _50;
    /* 0x90 */ SharedLock _90;
    /* 0xc8 */ SharedLock _c8;
    u8 _100[0x178 - 0x100];
};
KSYS_CHECK_SIZE_NX150(HavokAI, 0x178);

}  // namespace ksys::phys
