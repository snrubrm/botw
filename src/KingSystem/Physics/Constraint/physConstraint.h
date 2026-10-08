#pragma once

#include <math/seadMatrix.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadSpinLock.h>

class hkpConstraintInstance;

namespace ksys::phys {

class RigidBody;
class StaticCompoundRigidBodyGroup;

// Placeholder (the object at Constraint +0x18; its +8 is read by the two helpers).
struct ConstraintUnk18 {
    // 0x7100f6c658
    bool sub_7100F6C658() const;
    // 0x7100f6c64c: stores `value` in the object at +8 (+0x44).
    void sub_7100F6C64C(f32 value);
};

class Constraint {
    SEAD_RTTI_BASE(Constraint)

public:
    // lane4 s64: the index of the two bodies a constraint joins (`_30` / `_40` are two-element arrays; SEAD_ENUM
    // because 0x7100f6a69c spills its index parameter like SEAD_ENUM parameters do).
    SEAD_ENUM(BodyIndex, _0, _1)

    // FIXME: types
    Constraint();
    virtual ~Constraint();

    /// No-op if instance is null.
    static void destroy(Constraint* instance);

    // Placeholder names. Requests are recorded in _52 (bit 0, 1, 2) and the constraint is queued
    // on the RigidBodyRequestMgr when the first one is made.
    // 0x7100f6a2e0 (placeholder name): true when `mBodies[0]` is set, else whether `mBodies[1]` is set.
    bool sub_7100F6A2E0() const;
    // 0x7100f6ace8: whether a bit 0 request is pending (_52 bit 0).
    bool sub_7100F6ACE8() const;
    // 0x7100f6a880 (placeholder name): whether a bit 1 request is pending (_52 bit 1).
    bool sub_7100F6A880() const;
    // 0x7100f69ff0: requests bit 0 (cancels a pending bit 1 request instead if there is one).
    void sub_7100F69FF0();
    // 0x7100f6a074: requests bit 1 if _50 bit 0 is set (cancels a pending bit 0 request instead).
    void sub_7100F6A074();
    // 0x7100f6a0fc: requests bit 2 and stores the two values (_98, _9c).
    void sub_7100F6A0FC(f32 a, f32 b);
    // 0x7100f6a1d8: sub_7100F6A6F8(true, true) if a bit 1 request is pending.
    void sub_7100F6A1D8();
    // 0x7100f6a21c
    void sub_7100F6A21C();
    // 0x7100f6a6f8
    void sub_7100F6A6F8(bool a1, bool a2);
    // 0x7100f6aaa4 (lane4 s49; declared only, 308 B): attaches the constraint to the two bodies.
    void sub_7100F6AAA4(RigidBody* a, RigidBody* b);
    // 0x7100f6abd8: mBodies[idx] (idx clamped to 0-1), falling back to mFallbackBodies[idx].
    RigidBody* x_0(int idx) const;
    // 0x7100f6a69c (lane4 s64; placeholder names): clears body `idx` and the bit 3 (0x8) request.
    void sub_7100F6A69C(BodyIndex idx);
    // 0x7100f6a88c / 0x7100f6a92c: set body 0 / 1 and request bit 3 (0x8); false (nothing done) when a
    // bit 1 request is pending.
    bool sub_7100F6A88C(RigidBody* body);
    bool sub_7100F6A92C(RigidBody* body);
    // 0x7100f6a9d4: sub_7100F6A92C with the body looked up in the StaticCompoundMgr; false when there is none.
    bool sub_7100F6A9D4(StaticCompoundRigidBodyGroup* group);
    // 0x7100f6ac04: switches the hk constraint between PSI (false) and TOI priority and records it in _50 bit 4.
    void sub_7100F6AC04(bool toi);
    // 0x7100f6ac68: true when the body 1 (x_0(1)) is null or System's `_190` object.
    bool sub_7100F6AC68() const;
    // 0x7100f6d420 (lane4 s49; declared only, 696 B): sets the pivot transforms (the matrices are converted to
    // quaternions and positions).
    void sub_7100F6D420(const sead::Matrix34f& a, const sead::Matrix34f& b, const sead::Matrix34f& c);

    // inline-only in the original; see physConstraint.cpp.
    bool setBodyAndRequest_(BodyIndex idx, RigidBody* body);

    /* 0x08 */ hkpConstraintInstance* mConstraintInstance;
    /* 0x10 */ u32 _10;
    /* 0x18 */ ConstraintUnk18* _18;
    /* 0x20 */ void* _20;
    /* 0x28 */ void* _28;
    // lane4 s64 (from the ctor 0x7100f69d38 and x_0): the constraint's two bodies are `_40` (ctor arguments, set by
    // sub_7100F6A88C / A92C / A9D4); `_30` is the fallback x_0 uses for an empty slot ({System::_190, nullptr}).
    /* 0x30 */ sead::SafeArray<RigidBody*, 2> mFallbackBodies;
    /* 0x40 */ sead::SafeArray<RigidBody*, 2> mBodies;
    /* 0x50 */ u16 _50;
    /* 0x52 */ u16 _52;
    /* 0x58 */ sead::CriticalSection mCS;
    /* 0x98 */ f32 _98;
    /* 0x9c */ f32 _9c;
    /* 0xa0 */ void* _a0;
    /* 0xa8 */ sead::SpinLock _a8;
};

// 0x7100f6ac60 (lane4 s64; placeholder name): out-of-line in the Constraint TU, returns `instance->m_userData` (the
// ctor stores the Constraint there). RigidBodyRequestMgr::x_5 / x_6 tail-call it when adding / removing fails.
u64 sub_7100F6AC60(const hkpConstraintInstance* instance);

}  // namespace ksys::phys
