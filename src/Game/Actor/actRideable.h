#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys {
class Message;
namespace act {
class Actor;
}  // namespace act
}  // namespace ksys

namespace uking::act {

// Placeholder name (ctor 0x7100e8b2b8, D1 0x7100e8b304, vtable 0x71024ec660, 17 slots, size 0x40;
// CSV "Rideable::ProcLink::*"). Second base of Rideable (at +0x180) and the object returned by
// Actor vtable slot 133 (Enemy: &rideable->base, Motorcycle: _1648). Virtuals that Rideable
// overrides together with a RideableBase virtual carry the RideableBase name (one function
// overrides both); the others are named after their primary slot in Rideable.
class Unk_7100e8b2b8 {
public:
    Unk_7100e8b2b8();
    virtual ~Unk_7100e8b2b8();

    /*  2 */ virtual bool m4(ksys::act::Actor* actor, sead::Heap* heap);
    /*  3 */ virtual void m6();
    /*  4 */ virtual bool m17() { return false; }
    /*  5 */ virtual void m7();
    /*  6 */ virtual void m8() {}
    /*  7 */ virtual bool m22(int a1);
    /*  8 */ virtual void procLink8() { _c = 1; }
    /*  9 */ virtual bool m25() { return false; }
    /* 10 */ virtual f32 m26() { return 0.0f; }
    /* 11 */ virtual f32 m27() { return 0.0f; }
    /* 12 */ virtual f32 m28() { return 0.0f; }
    /* 13 */ virtual f32 procLink13() { return 0.0f; }
    /* 14 */ virtual bool m10(const ksys::Message& message);
    /* 15 */ virtual void m42(int a1) {}
    /* 16 */ virtual void m43() {}

    /* 0x08 */ sead::Atomic<u32> _8 = 0;
    /* 0x0c */ sead::Atomic<u32> _c = 0;
    /* 0x10 */ sead::Atomic<u32> _10 = 0;
    /* 0x18 */ ksys::act::Actor* mActor = nullptr;
    /* 0x20 */ ksys::act::BaseProcLink _20;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ u32 _38 = 0;
};

// Name from the CSV (RideableBase::*). vtable 0x71024eae60 (17 slots), size 0x180,
// factory RideableBase::make. Returned by Actor vtable slot 132 (Enemy::_1168, HorseBase::_b10).
// TODO: incomplete. Members are public: AI code reads them directly.
class RideableBase {
    SEAD_RTTI_BASE(RideableBase)
public:
    // CSV RideableBase::S1 (ctor 0x7100e7459c, size 0x88)
    struct S1 {
        S1();

        /* 0x00 */ void* _0;
        /* 0x08 */ u8 _8;
        /* 0x09 */ u8 _9;
        /* 0x0a */ u8 _a;
        /* 0x0b */ u8 _b;
        /* 0x0c */ f32 _c;
        /* 0x10 */ u32 _10;
        /* 0x18 */ u64 _18;
        /* 0x20 */ f32 _20;
        /* 0x24 */ f32 _24;
        /* 0x28 */ u32 _28;
        /* 0x2c */ u16 _2c;
        /* 0x2e */ u8 _2e;
        /* 0x2f */ u8 _2f;
        /* 0x30 */ sead::SafeString _30;
        /* 0x40 */ sead::SafeString _40;
        /* 0x50 */ u16 _50;
        /* 0x52 */ u16 _52;
        /* 0x58 */ sead::SafeString _58;
        /* 0x68 */ sead::SafeString _68;
        /* 0x78 */ sead::SafeString _78;
    };

    // CSV RideableBase::S2 (ctor 0x7100e6fa10, empty out-of-line dtor 0x7100e6fab0, size 0x90)
    struct S2 {
        S2();
        ~S2();

        u8 _0[0x90];
    };

    static RideableBase* make(sead::Heap* heap);

    RideableBase();
    virtual ~RideableBase();

    /*  4 */ virtual bool m4(ksys::act::Actor* actor, sead::Heap* heap);
    /*  5 */ virtual void m5();
    /*  6 */ virtual void m6() {}
    /*  7 */ virtual void m7();
    /*  8 */ virtual void m8() {}
    /*  9 */ virtual void m9();
    /* 10 */ virtual bool m10(const ksys::Message& message);
    /* 11 */ virtual int m11(int a1);
    /* 12 */ virtual f32 m12() { return 0.0f; }
    /* 13 */ virtual void* m13() { return nullptr; }
    /* 14 */ virtual f32 m14() { return 1.0f; }
    /* 15 */ virtual void m15() {}
    /* 16 */ virtual void m16(f32 value) {}

    /* 0x008 */ sead::Atomic<u32> _8 = 0;  // flags
    /* 0x010 */ ksys::act::Actor* mActor = nullptr;
    /* 0x018 */ S1 _18;
    /* 0x0a0 */ S2 _a0;
    /* 0x130 */ u64 _130 = 0;
    /* 0x138 */ f32 _138 = 0;
    /* 0x13c */ f32 _13c = 0;
    /* 0x140 */ u64 _140 = 0;
    /* 0x148 */ sead::Vector3f _148 = sead::Vector3f::zero;
    /* 0x154 */ f32 _154 = 1.0;
    /* 0x158 */ sead::Vector3f _158 = sead::Vector3f::zero;
    /* 0x164 */ f32 _164 = 1.0;
    /* 0x168 */ int _168 = 4;
    /* 0x170 */ u64 _170 = 0;
    /* 0x178 */ u32 _178 = 0;
};
KSYS_CHECK_SIZE_NX150(RideableBase, 0x180);

// Name from the CSV (Rideable::*). vtable 0x71024ec2e8 (45 slots), size 0x280, RTTI static
// 0x71025ae9f0. Returned by Actor vtable slot 131 (Enemy: DynamicCast<Rideable>(_1168)).
// Derived: RideableEnemy (vtable 0x71023cf460), RideableHorse (vtable 0x71024ec0c8).
// TODO: incomplete.
class Rideable : public RideableBase, public Unk_7100e8b2b8 {
    SEAD_RTTI_OVERRIDE(Rideable, RideableBase)
public:
    Rideable();
    ~Rideable() override;

    bool m4(ksys::act::Actor* actor, sead::Heap* heap) override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m9() override;
    bool m10(const ksys::Message& message) override;
    void m16(f32 value) override { _250 = value; }

    /* 17 */ bool m17() override { return true; }
    /* 18 */ virtual f32 m18() { return 0.0f; }
    /* 19 */ virtual bool m19() { return false; }
    /* 20 */ virtual void m20() {}
    /* 21 */ virtual bool m21() { return false; }
    /* 22 */ bool m22(int a1) override;
    // callers and overrides copy the result through the stack: probably a SEAD_ENUM
    /* 23 */ virtual int m23();
    /* 24 */ virtual void m24();
    /* 25 */ bool m25() override { return false; }
    /* 26 */ f32 m26() override { return 0.0f; }
    /* 27 */ f32 m27() override { return 0.0f; }
    /* 28 */ f32 m28() override { return 0.0f; }
    /* 29 */ virtual void m29() {}
    /* 30 */ virtual f32 m30() { return m31(); }
    /* 31 */ virtual f32 m31() { return 1.0f; }
    /* 32 */ virtual f32 m32() { return 0.0f; }
    /* 33 */ virtual f32 m33() { return 0.0f; }
    /* 34 */ virtual f32 m34() { return 0.0f; }
    /* 35 */ virtual f32 m35() { return 0.0f; }
    /* 36 */ virtual f32 m36() { return 0.0f; }
    /* 37 */ virtual f32 m37() { return 0.0f; }
    /* 38 */ virtual f32 m38() { return 0.0f; }
    /* 39 */ virtual void* m39() { return nullptr; }
    /* 40 */ virtual void* m40();
    /* 41 */ virtual void* m41() { return nullptr; }
    /* 42 */ void m42(int a1) override;
    /* 43 */ void m43() override {}
    /* 44 */ virtual bool m44();

    /* 0x1bc */ u32 _1bc = 0;
    /* 0x1c0 */ u32 _1c0 = 0;
    /* 0x1c4 */ sead::Matrix34f _1c4 = sead::Matrix34f::ident;
    /* 0x1f4 */ sead::Vector3f _1f4 = sead::Vector3f::zero;
    /* 0x200 */ sead::Matrix34f _200 = sead::Matrix34f::ident;
    /* 0x230 */ sead::Vector3f _230 = sead::Vector3f::zero;
    /* 0x23c */ sead::Vector3f _23c = sead::Vector3f::zero;
    /* 0x248 */ u64 _248 = 0;
    /* 0x250 */ f32 _250 = 2.0;
    /* 0x254 */ f32 _254 = -1.0;
    /* 0x258 */ sead::Vector2f _258 = sead::Vector2f::zero;
    /* 0x260 */ u64 _260 = 0;
    /* 0x268 */ u64 _268 = 0;
    /* 0x270 */ sead::Vector2f _270 = sead::Vector2f::zero;
    /* 0x278 */ u16 _278 = 0;
};
KSYS_CHECK_SIZE_NX150(Rideable, 0x280);

}  // namespace uking::act
