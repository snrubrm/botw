#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Ai/Pathfinding/Utilities/hkaiUserEdgeUtils.h>
#include <limits>
#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <math/seadBoundBox.h>
#include <thread/seadEvent.h>
#include "KingSystem/Utils/Container/LockFreeQueue.h"
#include <thread/seadCriticalSection.h>
#include <thread/seadThread.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

class hkaiWorld;
class hkaiStreamingCollection;
class hkaiSilhouetteGenerator;
class hkaiObstacleGenerator;
class hkpRigidBody;

// Game/AI/aiUnk_NavMeshCallback.h
class Unk_NavMeshCallback;

namespace ksys::res {
class Handle;
}

namespace ksys::phys {

// The nav mesh face event: a sead::Event whose reference count (at +0x30) the HavokAI shared
// locks use as their holder count, so a query result can keep the lock's event alive.
// Defined here because HavokAI::SharedLock holds one by value.
class Unk_7100f7e9f0Event {
public:
    sead::Event mEvent;
    sead::Atomic<s32> mRefCount;
};
static_assert(offsetof(Unk_7100f7e9f0Event, mRefCount) == 0x30);


enum class NavMeshSubMaterial;

class HavokAI;
class Unk_7102519a98;
class RigidBody;
class NavMeshCharacter;
class Unk_7100f7e9f0;

// NavMeshSystemThread (ctor 0x7100f89514, D0 0x7100f897a8, calc_ 0x7100f8972c,
// vtable 0x71024f70b0): HavokAI's navmesh worker thread (HavokAI::_38).
// Whole HavokAI::init allocates 110 bytes and passes (this, heap) to F89514.
// Complete SDK Thread owns the secondary base at 30; whole table starts 24F70A0.
class NavMeshSystemThread : public sead::Thread {
public:
    NavMeshSystemThread(HavokAI* system, sead::Heap* heap);
    void calc_(sead::MessageQueue::Element msg) override;

    // 0x7100f895fc (placeholder name): unless stopped (_10c), accumulates `dt` in _108 and sends the 'step' message.
    void sub_7100F895FC(f32 dt);
    // Whole F8962C stops stepping, drains the message queue and restores Thread priority.
    void sub_7100F8962C();

    u8 _pad[0x100 - sizeof(sead::Thread)];
    /* 0x100 */ HavokAI* _100;
    /* 0x108 */ f32 _108;
    /* 0x10c */ bool _10c;
};
KSYS_CHECK_SIZE_NX150(NavMeshSystemThread, 0x110);

// Placeholder name: the abstract base of the navmesh query requests that AI / horse code allocates from
// NavMeshQueryRequestPool's heap and hands to HavokAI::submitQuery / destroyQuery. Every query vtable starts
// with the same slots: an empty D1 (0x71000e43e8 for the trivial ones), D0, reset 0x71000e4348 and process.
class NavMeshQuery {
public:
    virtual ~NavMeshQuery() {}
    // 0x71000e4348 (shared): marks the query idle.
    virtual void reset() { _8 = 0; }
    // Runs the query; called with the HavokAI instance (0x71000e4350 for Unk_7102372790, 0x7100f809e4 for
    // NavMeshFaceQuery).
    virtual void process(HavokAI* ai) = 0;

    /* 0x08 */ u8 _8 = 0;  // 0: idle, 1: queued, 2: processed (NavMeshQueryRequestPool)
    /* 0x09 */ bool _9 = false;  // set by destroyQuery before it is queued
};

// Placeholder name (vtable 0x7102372790: D1 0x71000e43e8, D0 0x71000e4344, reset, process 0x71000e4350): a
// position query that WolfLinkAmiibo derives from (vtable 0x71024ed690) and CreateEpona / HorseSwimAction use.
// The fields come from process: 0x10 is an 8-byte result slot passed to the ray query, 0x18 the query position.
class Unk_7102372790 : public NavMeshQuery {
public:
    // 0x71000e4350
    void process(HavokAI* ai) override;

    /* 0x0a */ u8 _a[6];
    /* 0x10 */ u8 _10[8];  // opaque result slot handed to the ray collector (this + 0x10)
    /* 0x18 */ sead::Vector3f _18;
    /* 0x24 */ f32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2c */ s8 _2c;
    u8 _2d[3];
    /* 0x30 */ f32 _30;
};

// Placeholder name (vtable 0x710239b220, address point 0x710239b230, object size 0x28, process 0x71001a2f2c):
// the spawn-position query MotorcycleMgr::sub_7100679B30 and HorseMoveToSafePos::sub_71001A25D4 allocate
// (0x28 bytes, _8 zero, _c = the copied position, _24 = 0x17).
class Unk_710239b220 : public NavMeshQuery {
public:
    /* 0x0a */ u8 _a[2];
    /* 0x0c */ sead::Vector3f _c;
    /* 0x18 */ u64 _18;
    /* 0x20 */ u32 _20;
    /* 0x24 */ u32 _24;
};
KSYS_CHECK_SIZE_NX150(Unk_710239b220, 0x28);

// Placeholder name: the callback interface of the face searches (HavokAI::sub_7100F87334). Its m1 / m2
// defaults are 0x71000e43d0 / 0x71000e43e0 (not Unk_NavMeshCallback's out-of-line copies).
class NavMeshFaceCallback {
public:
    // Visits one face; returning true takes it.
    virtual bool m0(const Unk_7100f7e9f0& face) = 0;
    virtual void* m1() { return nullptr; }
    virtual bool m2() { return true; }
};

// Placeholder name (RTTI root; typeinfo static 0x71025b3c00, emitted with the HorseMoveToSafePos TU): a query
// bound to a character. NavMeshCharacter::_2e0 holds one; HorseMoveToSafePos casts it to its own query class.
class NavMeshCharacterQuery : public NavMeshQuery {
    SEAD_RTTI_BASE(NavMeshCharacterQuery)
public:
    /* 0x10 */ NavMeshCharacter* mCharacter = nullptr;
};

// Placeholder name (typeinfo static 0x71025b3bf0, Derive vtable 0x710239b208): searches the faces within
// mRadius of mPos (or of the character when mPos is NaN) and passes them to m0. The leaves (HorseMoveToSafePos's
// query: typeinfo 0x71025b3be0, vtable 0x710239b178, 0x50 bytes; HorseSwimAction's: typeinfo 0x7102602e80,
// 0x58 bytes) override m0 / m1 and keep the face they take.
class NavMeshFaceQuery : public NavMeshCharacterQuery, public NavMeshFaceCallback {
    SEAD_RTTI_OVERRIDE(NavMeshFaceQuery, NavMeshCharacterQuery)
public:
    // 0x7100f809e4
    void process(HavokAI* ai) override;

    /* 0x20 */ sead::Vector3f mPos;
    /* 0x2c */ f32 mRadius;
    /* 0x30 */ bool _30;
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
    // 0x7100f8aa78 (placeholder name): updates the transform of the entry `index` + 1 of the loaded resource.
    void sub_7100F8AA78(s32 index, const sead::Matrix34f& transform);

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

// Placeholder (the 0xb0-byte entries of InstanceSet::_100): HavokAI queues
// them for adding / removing (0x7100f8305c, 0x7100f83118, 0x7100f833a8). `_a0` is the HavokAI that should handle
// the next request (exchanged with ldxr/stxr, compared against `this | 1`), `_a8` request flags (ldxr/stxr
// and / orr in those functions: sead::Atomic).
struct NavMeshObjMaybe {
    // Native 0x7100f7f5ac / 0x7100f7f604 and the two-slot vtable 0x71024f6d00.
    NavMeshObjMaybe();
    virtual ~NavMeshObjMaybe();
    // 0x7100f7f6a0 unregisters the object and releases both generators.
    void sub_7100F7F6A0();
    // Whole 0x7100e8e92c supplies a BoxRigidBody, mode 2, bool, Fire submaterial,
    // zero group and SafeString name. This forwards to 0x7100f7ef9c, whose other
    // whole producer 0x7100fbfd54 supplies modes 0..3, bool, the parsed
    // NavMeshSubMaterial, a u16 group and InstanceSet's SafeString name.
    void sub_7100F7EF8C(RigidBody* body, u32 mode, bool forceTolerance,
                       NavMeshSubMaterial material, u16 group, const sead::SafeString& name);
    // Library generator construction remains undecompiled; no packet/layout substitution.
    void sub_7100F7EF9C(hkpRigidBody* body, u32 mode, bool forceTolerance,
                       NavMeshSubMaterial material, u16 group, const sead::SafeString& name);
    // 0x7100f7f428 forwards the rigid body's Havok body to the next native method.
    bool sub_7100F7F428(RigidBody* body);
    // 0x7100f7f430 returns whether the body change queued a HavokAI update.
    bool sub_7100F7F430(hkpRigidBody* body);
    void sub_7100F7FAC8(bool on);
    void sub_7100F7FB0C(bool on);
    enum class Flag : u32 {
        _1 = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
        _10 = 1 << 4,
        _20 = 1 << 5,
        _40 = 1 << 6,
    };

    // 0x7100f83460 / 0x7100f834cc pass these to hkaiWorld's generator operations.
    /* 0x08 */ hkaiSilhouetteGenerator* _8;
    /* 0x10 */ hkaiObstacleGenerator* _10;
    // Constructor and destructor independently establish the hkArray lifetime;
    // collector 0x710157ca0c appends transformed vectors and vertex counts,
    // while 0x7100f7f964 passes both arrays to generator update 0x7101531a84.
    /* 0x18 */ hkArray<hkVector4> mVertices;
    /* 0x28 */ hkArray<hkInt32> mVertexCounts;
    /* 0x38 */ u8 _38[0x58 - 0x38];
    /* 0x58 */ sead::CriticalSection mCriticalSection;
    /* 0x98 */ HavokAI* _98;  // the HavokAI it was added to
    /* 0xa0 */ sead::Atomic<HavokAI*> _a0;
    /* 0xa8 */ sead::TypedBitFlag<Flag, sead::Atomic<u32>> _a8;
    // 0x7100f7ef9c packs two u16 values here; 0x7100f7fac8 tests the low half.
    /* 0xac */ u32 _ac;
};
KSYS_CHECK_SIZE_NX150(NavMeshObjMaybe, 0xb0);

// Placeholder (the object 0x7100f8b518 / 0x7100f8b538 pass to HavokAI 0x7100f83580 / 0x7100f8363c / 0x7100f83790):
// same request scheme as NavMeshObjMaybe with the HavokAI at +0x70, the pending one at +0x78 and the flags at +0x80.
struct NavMeshObj2Maybe {
    // UserEdgeActor E8F95C submits its edge record with the fallback HavokAI.
    void sub_7100F8B518(HavokAI* fallback);
    void sub_7100F8B538();
    void sub_7100F8B584(hkaiStreamingCollection* collection);
    // Full F8B59C appends the same reflected pairs to its optional output array.
    void sub_7100F8B59C(hkArray<hkaiUserEdgeUtils::UserEdgePair>* out_pairs,
                      hkaiStreamingCollection* collection, s32 section);
    /* 0x00 */ u8 _0[0x60];
    // F8B59C produces 50-byte pairs; F8B9F0 filters UIDs. Outer E8FF20 clears and frees this array.
    hkArray<hkaiUserEdgeUtils::UserEdgePair> mPairs;
    /* 0x70 */ HavokAI* _70;
    /* 0x78 */ sead::Atomic<HavokAI*> _78;
    /* 0x80 */ sead::Atomic<u32> _80;
    u8 _84[4];
    // F80B20 sets the edge list's node offset; E8F750 constructs A0-byte outer entries.
    /* 0x88 */ sead::ListNode mNode;
};
KSYS_CHECK_SIZE_NX150(NavMeshObj2Maybe, 0x98);

// Name from the CSV (NavMeshQueryRequestPool::ctor 0x71012a8ffc, heap name
// "NavMeshQueryRequestPool"). Owns the request heap and lock-free request queues.
// TODO: incomplete.
class NavMeshQueryRequestPool {
public:
    // 0x71012a9ee8: sets query->_9 and pushes it to the queue at +0x180.
    void sub_71012A9EE8(NavMeshQuery* query);
    // 0x71012a9f68: pushes the query to the queue at +0x180; false if it is null or the queue is full.
    bool sub_71012A9F68(NavMeshQuery* query);
    // 0x71012aa000 (declared only): sets query->_9 = 1.
    void sub_71012AA000(NavMeshQuery* query);

    // 0x71012aa080 (same as sub_71012A9F68), 0x71012aa118 / 0x71012aa1f0: remove `query` / the character
    // from the queues (under the lock at +8 / +0x48).
    bool sub_71012AA080(NavMeshQuery* query);
    void sub_71012AA118(NavMeshQuery* query);
    void sub_71012AA1F0(NavMeshCharacter* nav);
    // 0x71012aa270 / 0x71012aa2f0 (placeholder names): remove `obj` from the queue at +0x150 / +0x168.
    void sub_71012AA270(NavMeshObjMaybe* obj);
    void sub_71012AA2F0(NavMeshObj2Maybe* obj);

    /* 0x000 */ u8 _0[8];
    /* 0x008 */ sead::CriticalSection _8;
    /* 0x048 */ sead::CriticalSection _48;
    /* 0x088 */ sead::CriticalSection _88;  // guards _150 (0x71012aa270)
    /* 0x0c8 */ sead::CriticalSection _c8;  // guards _168 (0x71012aa2f0)
    // Untyped: 0x7100f81a00 pushes an Unk_7102519a98 and 0x7100f81ee0 removes it (both go through
    // sub_71012aa118, which only compares pointers).
    /* 0x108 */ Unk_RequestQueue<void> _108;
    /* 0x120 */ Unk_RequestQueue<void> _120;
    /* 0x138 */ util::LockFreeQueue<NavMeshCharacter> _138;  // pushed by HavokAI::sub_7100F82BCC
    // The push loop of 0x7100f8305c etc. matches util::LockFreeQueue (same 0x18-byte layout as Unk_RequestQueue).
    /* 0x150 */ util::LockFreeQueue<NavMeshObjMaybe> _150;
    /* 0x168 */ util::LockFreeQueue<NavMeshObj2Maybe> _168;
    /* 0x180 */ Unk_RequestQueue<NavMeshQuery> _180;
    /* 0x198 */ NavMeshQuery* _198;
    // The heap the query requests are allocated from (callers call tryAlloc on it directly).
    /* 0x1a0 */ sead::Heap* mHeap;
};

// Name from the CSV (HavokAI::createInstance 0x7100f80b20, init 0x7100f80f38, ...). A polymorphic sead
// singleton (vtable 0x71024f6e88: D1 0x7100f80c60, D0 0x7100f80eb8; size 0x178; instance pointer at
// 0x710260de68). Members known from createInstance / init / the dtor: NavMeshSystemThread* at +0x38,
// NavMeshQueryRequestPool* at +0x40, a CriticalSection at +0x50, two sead::Events at +0x90 / +0xc8,
// three offset lists at +0x100 / +0x118 / +0x130. Only what callers use is declared so far.
// 0x7101ec27f8 (lane4 s102; GOT-loaded f32 3.5): default radius of HavokAI::Unk2. Declared only.
extern const f32 sUnk_7101ec27f8;

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

    // Placeholder (lane4 s102): input of sub_7100F86324, built on the stack by 0x710072edfc. Defaults from
    // that function: tolerance -1, _10 = Vector3f::zero, dir = Vector3f::ex, distance -1, radius from the
    // global 3.5 at 0x7101ec27f8. `from` and `_30` have no default; `_34` is not written by the caller
    // (sub_7100F86324 passes its address on to 0x7100f86334).
    struct Unk2 {
        sead::Vector3f from;
        f32 tolerance = -1.0f;
        sead::Vector3f _10 = sead::Vector3f::zero;
        sead::Vector3f dir = sead::Vector3f::ex;
        f32 distance = -1.0f;
        f32 radius = sUnk_7101ec27f8;
        u8 _30;
        u32 _34;
    };
    static_assert(sizeof(Unk2) == 0x38);

    // 0x7100f86324: runs sub_7100F86334 on `query` for the character `nav`, with `&query._34` added;
    // `result` may be null. True if it hit.
    bool sub_7100F86324(NavMeshCharacter* nav, const Unk2& query, Unk1* result);

    // 0x7100f86174: a navmesh query from `from` towards `to` (`a4`: a height
    // tolerance); true if it hit.
    bool sub_7100F86174(const sead::Vector3f& from, const sead::Vector3f& to, Unk1* result, f32 a4);

    // 0x7100f86334 (424 B): sub_7100F8688C under _90, or sub_7100F864DC under _c8.
    bool sub_7100F86334(NavMeshCharacter* nav, const Unk2& query, const u32* tail, Unk1* result);
    // 0x7100f8688c / 0x7100f864dc (unnamed, declared only): the query bodies under _90 / _c8.
    bool sub_7100F8688C(NavMeshCharacter* nav, const Unk2& query, const u32* tail, Unk1* result);
    bool sub_7100F864DC(NavMeshCharacter* nav, const Unk2& query, const u32* tail, Unk1* result);

    // 0x7100f87ed0 (CSV HavokAI::__auto3, declaration only): the HavokAI counterpart of
    // NavMeshCharacter::sub_7100F76078 (closest navmesh point to `to`, written to `out`).
    Unk_7100f7e9f0 sub_7100F87ED0(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);
    // 0x7100f87c40 / 0x7100f87d88 (unnamed, declared only): the bodies under _90 / _c8 of sub_7100F87ED0.
    Unk_7100f7e9f0 sub_7100F87C40(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);
    Unk_7100f7e9f0 sub_7100F87D88(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);

    // 0x7100f87a80 (declaration only): navmesh query between `from` and `to` (PriestBossMove::m35 passes the
    // point raised and lowered by 1), writing the hit point to `out`.
    Unk_7100f7e9f0 sub_7100F87A80(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to);
    // 0x7100f87760 / 0x7100f878f0 (unnamed, declared only): the bodies under _90 / _c8 of sub_7100F87A80.
    Unk_7100f7e9f0 sub_7100F87760(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to);
    Unk_7100f7e9f0 sub_7100F878F0(sead::Vector3f* out, const sead::Vector3f& from, const sead::Vector3f& to);

    // 0x7100f88b1c (unnamed in the CSV; not decompiled): NavMeshCharacter::sub_7100F76078 forwards here.
    Unk_7100f7e9f0 sub_7100F88B1C(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to,
                                  f32 a3);
    // 0x7100f8885c / 0x7100f889bc (unnamed, declared only): the bodies under _90 / _c8 of sub_7100F88B1C.
    Unk_7100f7e9f0 sub_7100F8885C(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to,
                                  f32 a3);
    Unk_7100f7e9f0 sub_7100F889BC(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to,
                                  f32 a3);
    // 0x7100f88cf8 (unnamed, declared only, 728 B): the query body under _c8 for a character (the face
    // event is the lock's event, which the result keeps).
    Unk_7100f7e9f0 sub_7100F88CF8(sead::Vector3f* out, Unk_7100f7e9f0Event* event, hkaiWorld* world,
                                  NavMeshCharacter* nav, const sead::Vector3f& to, f32 a3);

    // 0x7100f81ee0 (declaration only; placeholder name): under the lock, removes `obj` from the query pool and
    // its pending requests (unless `queued`), then unregisters it if flags 0x3c00 are set.
    void sub_7100F81EE0(Unk_7102519a98* obj, bool queued);
    // 0x7100f81a00 (declaration only; placeholder name): updates the transform of an added entry.
    void sub_7100F81A00(Unk_7102519a98* obj, const sead::Matrix34f& transform);

    // 0x7100f84194 (placeholder name; CSV guess HavokAI::getNavMeshLoadMgr): walks the +0x118 offset list and
    // the +0x28 object's +0xe0 array. Called by NavMeshSystemThread::sub_7100F8962C on timeout (declared only).
    void sub_7100F84194();

    // 0x7100f82bcc (CSV HavokAI::__auto2): registers a navmesh character: clears flag 2 / sets flag 1 of
    // its `_220`, stores this in its `_20` and queues it. Callers run it when `nav->_18` is null.
    void sub_7100F82BCC(NavMeshCharacter* nav);

    // 0x7100f8305c / 0x7100f83118 / 0x7100f833a8 (placeholder names): request bit 0 (clearing bit 1) / bit 2 /
    // bit 1 (clearing bit 0) for `obj` and queue it in the pool unless another HavokAI has it pending.
    void sub_7100F8305C(NavMeshObjMaybe* obj);
    void sub_7100F83118(NavMeshObjMaybe* obj);
    void sub_7100F833A8(NavMeshObjMaybe* obj);
    void sub_7100F83460(NavMeshObjMaybe* obj);
    void sub_7100F834CC(NavMeshObjMaybe* obj, bool queued);
    // 0x7100f831c0 / 0x7100f832b4 (placeholder names): set flag 8 / 0x20 and clear 0x10 / 0x40 (or the other way
    // round when `on` is false), then queue like sub_7100F8305C.
    void sub_7100F831C0(NavMeshObjMaybe* obj, bool on);
    void sub_7100F832B4(NavMeshObjMaybe* obj, bool on);
    // 0x7100f83580 / 0x7100f8363c (placeholder names): the same for NavMeshObj2Maybe (bit 0 / bit 2).
    void sub_7100F83580(NavMeshObj2Maybe* obj);
    void sub_7100F8363C(NavMeshObj2Maybe* obj);
    void sub_7100F83790(NavMeshObj2Maybe* obj, bool queued);
    void sub_7100F83848(const hkArray<hkaiUserEdgeUtils::UserEdgePair>* pairs);

    // 0x7100f82c88 (placeholder name): resets the character's path state (inlineReset) and queues it with bit 1
    // (clearing bit 0), like sub_7100F82BCC.
    void sub_7100F82C88(NavMeshCharacter* nav);

    // 0x7100f82dd8 (not decompiled): counterpart of sub_7100F82BCC (called with the same guard).
    void sub_7100F82DD8(NavMeshCharacter* nav);

    // 0x7100f8184c (CSV name): _38->sub_7100F895FC(dt).
    void sendStepMessageToNavMeshSysThread(f32 dt);
    // F81550 is the full locked navmesh step; the worker supplies its accumulated time.
    void sub_7100F81550(f32 dt);
    // 0x7100f8185c (placeholder name): clears the thread's stop flag (_38->_10c).
    void sub_7100F8185C();

    // 0x7100f8183c: starts the navmesh system thread (_38->start()).
    bool startNavMeshSystemThread();
    void sub_7100F81854();

    // 0x7100f88fd0 (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F760F0 forwards here.
    Unk_7100f7e9f0 sub_7100F88FD0(NavMeshCharacter* nav, sead::Vector3f* out, const sead::Vector3f& to,
                                    f32 value);

    // 0x7100f87594 (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F76168 / sub_7100F761C8 forward here
    // (`pos` may be null; `radius` is the character's `_2a8 * _2ac`).
    bool sub_7100F87594(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius, f32 value, bool flag,
                        NavMeshFaceCallback* callback);
    // 0x7100f87334 (declared only; 304 B): the face search of NavMeshFaceQuery::process (`pos` may be null;
    // `radius` is the character's `_2a8 * _2ac`).
    bool sub_7100F87334(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius, f32 search_radius,
                        bool flag, NavMeshFaceCallback* callback);

    // 0x7100f83a9c (unnamed in the CSV; declaration only): NavMeshCharacter::sub_7100F75AF0 forwards its query here.
    void sub_7100F83A9C(NavMeshQuery* query);

    // 0x7100f83a94 (CSV HavokAI::__auto4): hands the query back to the pool (NavMeshCharacter::finalize).
    void sub_7100F83A94(NavMeshQuery* query);

    // 0x7100f82f38 (unnamed; 292 B, declared only): detaches the character from this HavokAI.
    void sub_7100F82F38(NavMeshCharacter* character, bool unk);

    // 0x7100f83a84 / 0x7100f83a8c (CSV names).
    void destroyQuery(NavMeshQuery* query);
    bool submitQuery(NavMeshQuery* query);

    // inline-only in the original; name is a guess. A shared lock: up to 0x100 holders, the event is reset by the first
    // and signalled when the last one leaves. The same acquire / release sequence is inlined into 0x7100f857f4,
    // 0x7100f854c4 and 0x7100f8565c (for _90 and _c8).
    // The shared lock: the face event itself. Its reference count at +0x30 is the number of
    // holders, and the event is signalled when the last one leaves. The same object is handed to
    // the query results (their dtor releases a reference).
    struct SharedLock {
        bool tryLock() {
            while (true) {
                const u32 count = mEvent.mRefCount.load();
                if (count > 0xff)
                    return false;
                if (!mEvent.mRefCount.compareExchange(count, s32(count + 1)))
                    continue;
                if (count == 0)
                    mEvent.mEvent.resetSignal();
                return true;
            }
        }

        void unlock() {
            if (mEvent.mRefCount.decrement() == 1)
                mEvent.mEvent.setSignal();
        }

        Unk_7100f7e9f0Event mEvent;
    };

    // 0x7100f85c00 (696 B; declared only): the query sub_7100F86174 runs under _90 (sub_7100F85EB8 under _c8).
    bool sub_7100F85C00(f32 a4, const sead::Vector3f* from, const sead::Vector3f* to, Unk1* result);

    // 0x7100f85eb8 (700 B; declared only; was Unk_710260de68::sub_7100F85EB8): a line query from `from` to `to`
    // that answers whether something is in the way.
    bool sub_7100F85EB8(f32 radius, const sead::Vector3f* from, const sead::Vector3f* to, void* unused);

    // 0x7100f85a78 (declared only): the ray query behind sub_7100F85974 / sub_7100F87334 / sub_7100F87464.
    // `world` is _28 (under _90) or _30 (under _c8); `pos` is the 16-byte hkVector4f direction the caller builds;
    // `obj` (x3) only supplies the navmesh id through obj->_8->_98 and is null for a plain position query; `flag`
    // sets the query filter; `user` (x5) is the query payload / callback. The this pointer (x0) is not used.
    bool sub_7100F85A78(hkaiWorld* world, const hkVector4f* pos, void* obj, bool flag, void* user,
                        f32 a, f32 b, f32 c);
    // 0x7100f85974 (declared only): runs sub_7100F85A78 under _90.
    void sub_7100F85974(void* user, const sead::Vector3f* pos, bool flag, f32 a, f32 b, f32 c);
    // 0x7100f87464 (declared only): like sub_7100F87334 but under _c8 and with the _30 world.
    bool sub_7100F87464(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius, f32 search_radius,
                        bool flag, NavMeshFaceCallback* callback);

    // 0x7100f857f4 (placeholder name): visits the nav mesh nodes inside `aabb` with `callback` (0x7100f854c4 under _90, or 0x7100f8565c under _c8 if _90
    // is full). The callback is a caller-defined object (e.g. vtable 0x71023e7188).
    void sub_7100F857F4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);
    // 0x7100f854c4 / 0x7100f8565c (declared only).
    void sub_7100F854C4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);
    void sub_7100F8565C(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb);

    /* 0x28 */ hkaiWorld* _28;
    // 0x7100f87464 passes this where 0x7100f87334 passes _28 (the same ray query under the _c8 lock): a second world.
    /* 0x30 */ hkaiWorld* _30;
    NavMeshSystemThread* _38;
    NavMeshQueryRequestPool* _40;
    NavMeshLoadMgr* _48;
    /* 0x50 */ sead::CriticalSection _50;
    /* 0x90 */ SharedLock _90;
    /* 0xc8 */ SharedLock _c8;
    u8 _100[0x130 - 0x100];
    /* 0x130 */ sead::OffsetList<NavMeshObj2Maybe> mEdgeObjects;
    u8 _148[0x178 - 0x148];
};
KSYS_CHECK_SIZE_NX150(HavokAI, 0x178);

}  // namespace ksys::phys
