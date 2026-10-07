#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActorBind.h"

namespace ksys::act {
class Actor;
}

namespace ksys::phys {
class Constraint;
class RigidBody;
}

namespace sead {
class Heap;
}

// 0x7100f6d358 (declared only; placeholder name): creates a physics constraint on `heap` (nullptr on failure).
ksys::phys::Constraint* sub_7100F6D358(sead::Heap* heap);

// Unnamed carried-actor helper objects embedded in the AddCarriedBase family. Layouts come from the
// constructors (the classes have ~30 virtual / helper functions that are not decompiled).

// CSV: CarriedData (CarriedData::ctor 0x71006f3e40; vtable 0x7102450058).
class CarriedData {
public:
    explicit CarriedData(ksys::act::Actor* actor);
    virtual ~CarriedData();

    // 0x71006f5450 / 0x71006f4804 (CSV CarriedData::x_12 / x_13; declared only; called directly (devirtualised) by
    // Carried::leave_). The matrix / vector are passed by value.
    // 0x71006f9460 / 0x71006f8ad4 (CSV CarriedData::x / x_0) / 0x71006f3e80 / 0x71006f4f78 / 0x71006f4128 /
    // 0x71006f41f4 / 0x71006f536c / 0x71006f5484 (declared only; signatures from Carried::enter_).
    void x();
    void x_0();
    sead::Matrix34f x_1(const sead::Matrix34f& mtx);
    void x_2(sead::Matrix34f mtx);
    void x_3(f32 a, f32 b);
    void x_5();
    void x_6();
    void updateIsDroppedFlag();
    // 0x71006f4548 / 4df8 / 53bc / 9194 (x_4 / x_7 / x_8 / x_9), 8f24 (x_15), 4f30 / 8cb0 (x_16 / x_17), 8e60 (x_18),
    // 4440 (x_19), 8f90 / 8bd4 (x_20 / x_21), 8f40 (x_22), 908c (x_23); declared only (Carried::calc_).
    void x_4();
    void x_7();
    void x_8();
    void x_9();
    void x_16();
    void x_19();
    void x_21();
    void x_23(ksys::act::Actor* actor);
    void x_12();
    void x_13(sead::Matrix34f mtx, bool a2, sead::Vector3f pos);

    ksys::act::Actor* mActor;
    // 2026-10-07: sub_71006F8CB0 compares this state as signed.
    s32 _10 = 0;
    f32 _14 = sead::Mathf::pi() / 6;  // 0x3f060a92 (30 degrees)
    f32 _18 = 10.0f;
    f32 _1c = -1.0f;
    void* _20 = nullptr;
    f32 _28 = 1.0f;
    u8 _2c = 0;  // flag bits (1 / 0x10 / 0x20 tested by Carried::calc_)
};
KSYS_CHECK_SIZE_NX150(CarriedData, 0x30);

// vtable 0x7102450298 (ctor 0x71006f8a08). Embedded in AddCarriedBase (+0x68).
class Unk_7102450298 : public CarriedData {
public:
    explicit Unk_7102450298(ksys::act::Actor* actor);
    ~Unk_7102450298() override;

    // 0x71006f8a88 (CSV CarriedData::x_25): destroys the constraint.
    void finalize();

    /// 0x71006f8ab4 (lane1 s22, name is a placeholder): true without a constraint, else whether the
    /// constraint's low flag byte has bit 0 clear.
    bool sub_71006F8AB4() const;
    // 0x7100f6d358 + store; false when the constraint could not be created.
    bool init(sead::Heap* heap);

    // The non-virtual methods of the constraint-carried object (CSV CarriedData::x_*; lane4 s49: they read `_30`, so they
    // belong to this class; the CSV rows are renamed). Called by Carried::enter_ / calc_ / leave_.
    // 0x71006f8f14: `_30->sub_7100F6A074()`.
    void x_10();
    // 0x71006f8d58 (declared only).
    void x_11();
    // 0x71006f8f24: bit 0 of the constraint's `_50`.
    bool x_15();
    // 0x71006f8cb0 (declared only).
    void x_17(f32 mass);
    // 0x71006f8f90: hands the controller's velocity direction / horizontal speed back to its character controller.
    void x_20();
    // 0x71006f8e60: links the bodies of `mActor` and `actor` with the constraint.
    void x_18(ksys::act::Actor* actor);
    // 0x71006f8f40: moves the constraint to the actor's matrix and `body`'s transform.
    void x_22(ksys::phys::RigidBody* body);

    ksys::phys::Constraint* _30 = nullptr;
    f32 _38 = 1.0f;
    f32 _3c = 1.0f;
    f32 _40 = 1.0f;
    f32 _44 = 0.0f;
    // 2026-10-07: original x_11 passes +0x48 to RigidBody::setInertiaLocal as a vector.
    sead::Vector3f _48{1.0f, 1.0f, 1.0f};
    bool _54 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450298, 0x58);

// vtable 0x710244ed58 (ctor 0x71006e80f8): an ActorBind variant. Embedded in AddNodeNodeCarried (+0xc0).
class Unk_710244ed58 : public ksys::act::ActorBind {
public:
    Unk_710244ed58();
    // Inline in the original (embedded users' D1 / D0 inline it; no out-of-line copy).
    ~Unk_710244ed58() override = default;

    bool m4(ksys::act::BaseProc* proc) override;

    /* 0x28 */ const char* _28 = nullptr;  // name of the carried actor's node
    /* 0x30 */ const char* _30 = nullptr;  // own node name
    /* 0x38 */ s64 _38 = -1;
    /* 0x40 */ sead::Matrix34f _40 = sead::Matrix34f::ident;
    /* 0x70 */ u32 _70 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710244ed58, 0x78);

// 2026-10-07: original sub_71006F8CB0 references this constant local inertia.
extern const sead::Vector3f sUnk_7101e7b5c8;
