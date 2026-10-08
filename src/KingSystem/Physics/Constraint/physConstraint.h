#pragma once

#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadSpinLock.h>

class hkpConstraintInstance;

namespace ksys::phys {

class RigidBody;

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
    // FIXME: types
    Constraint();
    virtual ~Constraint();

    /// No-op if instance is null.
    static void destroy(Constraint* instance);

    // Placeholder names. Requests are recorded in _52 (bit 0, 1, 2) and the constraint is queued
    // on the RigidBodyRequestMgr when the first one is made.
    // 0x7100f6a2e0 (placeholder name): true when `_40` is set, else whether `_48` is set.
    bool sub_7100F6A2E0() const;
    // 0x7100f6ace8: whether a bit 0 request is pending (_52 bit 0).
    bool sub_7100F6ACE8() const;
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
    // 0x7100f6abd8: _40[idx] (idx clamped to 0-1), falling back to _30[idx].
    RigidBody* x_0(int idx);
    // 0x7100f6d420 (lane4 s49; declared only, 696 B): sets the pivot transforms (the matrices are converted to
    // quaternions and positions).
    void sub_7100F6D420(const sead::Matrix34f& a, const sead::Matrix34f& b, const sead::Matrix34f& c);

    /* 0x08 */ hkpConstraintInstance* mConstraintInstance;
    /* 0x10 */ u32 _10;
    /* 0x18 */ ConstraintUnk18* _18;
    /* 0x20 */ void* _20;
    /* 0x28 */ void* _28;
    /* 0x30 */ RigidBody* _30;
    /* 0x38 */ RigidBody* _38;
    // x_0 indexes _40/_48 and _30/_38 as two-element RigidBody* arrays (0x7100f6abd8).
    /* 0x40 */ RigidBody* _40;
    /* 0x48 */ RigidBody* _48;
    /* 0x50 */ u16 _50;
    /* 0x52 */ u16 _52;
    /* 0x58 */ sead::CriticalSection mCS;
    /* 0x98 */ f32 _98;
    /* 0x9c */ f32 _9c;
    /* 0xa0 */ void* _a0;
    /* 0xa8 */ sead::SpinLock _a8;
};

}  // namespace ksys::phys
