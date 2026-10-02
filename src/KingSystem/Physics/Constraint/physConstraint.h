#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadSpinLock.h>

class hkpConstraintInstance;

namespace ksys::phys {

class RigidBody;

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

    /* 0x08 */ hkpConstraintInstance* mConstraintInstance;
    /* 0x10 */ u32 _10;
    /* 0x18 */ void* _18;
    /* 0x20 */ void* _20;
    /* 0x28 */ void* _28;
    /* 0x30 */ RigidBody* _30;
    /* 0x38 */ RigidBody* _38;
    /* 0x40 */ void* _40;
    /* 0x48 */ void* _48;
    /* 0x50 */ u16 _50;
    /* 0x52 */ u16 _52;
    /* 0x58 */ sead::CriticalSection mCS;
    /* 0x98 */ f32 _98;
    /* 0x9c */ f32 _9c;
    /* 0xa0 */ void* _a0;
    /* 0xa8 */ sead::SpinLock _a8;
};

}  // namespace ksys::phys
