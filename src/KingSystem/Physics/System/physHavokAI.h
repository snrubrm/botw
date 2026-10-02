#pragma once

#include <limits>
#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class NavMeshCharacter;

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

    // 0x7100f82bcc (CSV HavokAI::__auto2): registers a navmesh character: clears flag 2 / sets flag 1 of
    // its `_220`, stores this in its `_20` and queues it. Callers run it when `nav->_18` is null.
    void sub_7100F82BCC(NavMeshCharacter* nav);

    // 0x7100f82dd8 (not decompiled): counterpart of sub_7100F82BCC (called with the same guard).
    void sub_7100F82DD8(NavMeshCharacter* nav);

    // 0x7100f83a84 / 0x7100f83a8c (CSV names).
    void destroyQuery(Unk_7102372790* query);
    bool submitQuery(Unk_7102372790* query);

    u8 _28[0x40 - 0x28];
    NavMeshQueryRequestPool* _40;
    u8 _48[0x178 - 0x48];
};
KSYS_CHECK_SIZE_NX150(HavokAI, 0x178);

}  // namespace ksys::phys
