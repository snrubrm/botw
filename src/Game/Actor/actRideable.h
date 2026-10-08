#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actUnk_7100d14598.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys {
class Message;
namespace act {
class Actor;
class BaseProc;
struct Unk117;
}  // namespace act
}  // namespace ksys

namespace ksys::as {
class ASList;
}

namespace ksys::phys {
class CharacterController;
}

namespace uking::act {

class HorseReins;

// Placeholder name (ctor 0x7100e8b2b8, D1 0x7100e8b304, vtable 0x71024ec660, 17 slots, size 0x40;
// CSV "Rideable::ProcLink::*"). Second base of Rideable (at +0x180) and the object returned by
// Actor vtable slot 133 (Enemy: &rideable->base, Motorcycle: _1648). Virtuals that Rideable
// overrides together with a RideableBase virtual carry the RideableBase name (one function
// overrides both); the others are named after their primary slot in Rideable.
class Unk_7100e8b2b8 {
public:
    // Placeholder enum (no enum text in the binary): the value kept in the low byte of _8, read by
    // value (stack store + reload) in the awareness filter 0x71007456fc, which treats 1 / 2 / 3 like
    // the TargetActorType names "Player" / "Enemy" / "NPC". m22 replaces it.
    SEAD_ENUM(Unk8, _0, _1, _2, _3)
    // Placeholder (bits of _10; MotorcycleWait::calc_ converts bit 6 through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6)
    // inline-only in the original (name is a guess): MotorcycleWait::calc_ evaluates the enum argument (stack round
    // trip) before the load of _10.
    bool isFlag10On(Flag flag) const {
        const u32 mask = 1u << int(flag);
        return (_10.load() & mask) != 0;
    }

    // Placeholder enum: the bit indices of the flag word _10 (the original round-trips them through the stack like
    // SEAD_ENUM values; 4, 5 and 7 are used so far).
    SEAD_ENUM(Flag10, _0, _1, _2, _3, _4, _5, _6, _7)

    Unk_7100e8b2b8();
    virtual ~Unk_7100e8b2b8();

    /*  2 */ virtual bool m4(ksys::act::Actor* actor, sead::Heap* heap);
    /*  3 */ virtual void m6();
    /*  4 */ virtual bool m17() { return false; }
    /*  5 */ virtual void m7();
    /*  6 */ virtual void m8() {}
    /*  7 */ virtual bool m22(Unk8 a1);
    /*  8 */ virtual void procLink8() { _c = 1; }
    /*  9 */ virtual bool m25() { return false; }
    /* 10 */ virtual f32 m26() { return 0.0f; }
    /* 11 */ virtual f32 m27() { return 0.0f; }
    /* 12 */ virtual f32 m28() { return 0.0f; }
    /* 13 */ virtual f32 procLink13();
    /* 14 */ virtual bool m10(const ksys::Message& message);
    /* 15 */ virtual void m42(int a1) {}
    /* 16 */ virtual void m43() {}

    ksys::act::Actor* sub_7100E8B644();
    ksys::act::Actor* sub_7100E8B6E0();
    // 0x7100e8bb4c: called with the base class' result by the isSpecialJobType_ overrides of Enemy, HorseBase and
    // Motorcycle (declaration only).
    // (BaseProc::IsSpecialJobTypeResult is protected, so the values are passed as ints.)
    int sub_7100E8BB4C(int result);
    // 0x7100e8bd6c: links `proc` in _20 (resets the link if null).
    void sub_7100E8BD6C(ksys::act::BaseProc* proc);
    // 0x7100e8bd80 / 0x7100e8be10: enable / disable the actor's "Ride", "Ride2" (the enable variant
    // only looks it up) and "JumpRide" attention clients.
    void sub_7100E8BD80();
    void sub_7100E8BE10();
    // 0x7100e8bfd4: sets bit 8 of _8; true if it was clear.
    bool sub_7100E8BFD4();
    // 0x7100e8b780: handles an Actor::x_17 request (vtable slot 117 of Enemy / HorseBase /
    // Motorcycle): false (the request is consumed) when it names the event "Demo005_0".
    bool sub_7100E8B780(ksys::act::Unk117* arg);
    // 0x7100e8c03c: the actor's HorseUnit RiddenAnimalType.
    // 0x7100e8bff4: `HorseMgr::instance()` (null: false) `->sub_7100E84AB8(mActor)`.
    bool sub_7100E8BFF4();
    // 0x7100e8c018: `HorseMgr::instance()` (null: false) `->isLinkedToActor(mActor)`.
    bool sub_7100E8C018();
    // The ridden animal type of the horse unit param (a 4-byte SEAD_ENUM by value: ActorConstDataAccess::sub_7100D14598
    // returns it unchanged, which is where the `and x0, x0, #0xffffffff` comes from).
    ksys::act::Unk_7100d14598 sub_7100E8C03C() const;
    // 0x7100e8c068: with Unk8 3, the previous position of the actor linked in _20.
    bool sub_7100E8C068(sead::Vector3f* pos);

    /* 0x08 */ sead::Atomic<u32> _8 = 0;
    /* 0x0c */ sead::Atomic<u32> _c = 0;
    /* 0x10 */ sead::Atomic<u32> _10 = 0;
    /* 0x18 */ ksys::act::Actor* mActor = nullptr;
    /* 0x20 */ ksys::act::BaseProcLink _20;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ f32 _38 = 0.0f;  // (read by res::AttCheckRideSpace::check as a height offset)
};

// Name from the CSV (RideableBase::*). vtable 0x71024eae60 (17 slots), size 0x180,
// factory RideableBase::make. Returned by Actor vtable slot 132 (Enemy::_1168, HorseBase::_b10).
// TODO: incomplete. Members are public: AI code reads them directly.
class RideableBase {
    SEAD_RTTI_BASE(RideableBase)
public:
    // CSV RideableBase::S1 (ctor 0x7100e7459c, size 0x88): the rider's AS (animation) controller; its
    // methods are in TU 0x7100e7459c-0x7100e78f00 (actRideableBaseS1.cpp).
    struct S1 {
        S1();

        void sub_7100E747E8(ksys::as::ASList* list);

        void sub_7100E74890(bool a1, bool a2, f32 a3, f32 a4);

        // 0x7100e76260: plays AS `name` (slot / bank arguments; placeholder signature).
        void sub_7100E76260(const sead::SafeString& name, int a2, int slot, int a4, int bank);
        // 0x7100e770c4: clears flag bits 0x600 (sets 0x10) and _40 unless 0x400 is set (or `force`).
        void sub_7100E770C4(bool force);
        // 0x7100e786f0: sub_7100E76260(name, 0, 0, 0, bank) with the bank picked from _2e.
        void sub_7100E786F0(const sead::SafeString& name);
        // 0x7100e76e74: requests AS `name` (compared with two global SafeStrings at 0x7102603110 /
        // 0x7102603180; priority from 0x7100e7712c kept in _51, name in _40); `a2` sets / clears bit 9
        // of _52. Returns false only when the request is rejected. Not decompiled yet.
        bool sub_7100E76E74(const sead::SafeString& name, bool a2);
        // 0x7100e76cec: the AS bank (_2e or 0) the animation requests use (0 if bit 1 of _52 is set).
        int sub_7100E76CEC();
        // 0x7100e787a0 / 0x7100e78e00: set bit 0x20 / 0x80 of _52.
        void sub_7100E787A0();
        void sub_7100E78E00();
        // lane4 s46 (placeholder names, from the bodies). 0x7100e76bbc: clears the request state (_18 / _28 / _2c,
        // _20 = -1, _24 = 1). 0x7100e7878c: sets _2d if it is clear.
        void sub_7100E76BBC();
        void sub_7100E7878C();
        // 0x7100e76d6c / 0x7100e76dc4 / 0x7100e76e1c: the AS list's x_5 (slot 0, bank _2e) with Unk2::sub_71011632F8 /
        // sub_710116323C / sub_7101163160 if x_4(0, 0) holds (0 / 0 / 1 otherwise).
        f32 sub_7100E76D6C();
        f32 sub_7100E76DC4();
        f32 sub_7100E76E1C();

        /* 0x00 */ ksys::as::ASList* _0 = nullptr;
        /* 0x08 */ u8 _8 = 0;
        /* 0x09 */ u8 _9 = 0;
        /* 0x0a */ u8 _a = 0;
        /* 0x0b */ u8 _b = 0;
        /* 0x0c */ f32 _c = 0;
        /* 0x10 */ u32 _10 = 0;
        /* 0x18 */ u64 _18 = 0;
        /* 0x20 */ f32 _20 = -1.0f;
        /* 0x24 */ f32 _24 = 1.0f;
        /* 0x28 */ u32 _28 = 0;
        /* 0x2c */ u8 _2c = 0;
        /* 0x2d */ u8 _2d = 0;
        /* 0x2e */ s8 _2e = 1;
        /* 0x2f */ u8 _2f = 3;
        /* 0x30 */ sead::SafeString _30;
        /* 0x40 */ sead::SafeString _40;
        /* 0x50 */ u8 _50 = 0;
        /* 0x51 */ u8 _51 = 0;
        /* 0x52 */ u16 _52 = 2;
        /* 0x58 */ sead::SafeString _58;
        /* 0x68 */ sead::SafeString _68;
        /* 0x78 */ sead::SafeString _78;
    };

    // CSV RideableBase::S2 (ctor 0x7100e6fa10, empty out-of-line dtor 0x7100e6fab0, size 0x90)
    struct S2 {
        S2();
        ~S2();

        u8 _0[0x88];
        /* 0x88 */ u16 _88 = 0;  // flags (bit 4 is tested by HorseRiddenByNPC::calc_)
        u8 _8a[0x90 - 0x8a];
    };

    // Placeholder (callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Rank, _0, _1, _2)

    static RideableBase* make(sead::Heap* heap);

    RideableBase();
    virtual ~RideableBase();

    bool getSomethingFromAnimalUnitSpeed();
    // 0x7100e63374 (lane4 s46, placeholder name): _140 if _138 > 0, else _144 if _13c > 0, else 0.
    u64 sub_7100E63374();

    // 0x7100e63224 (ForkAnimalASPlay::calc_): selects the next gear (`type` 1-5, else 0) unless
    // flag 4 of _8 is set. Both parameters are probably small by-value enum structs in the original.
    void sub_7100E63224(u64 type, u64 gear);
    // 0x7100e63424 (lane2 s20; declared only; PreyRoot::m43): sets or clears bit 1 of _18._52 depending on
    // a flag byte (+0xb8) of the first body of the actor's ragdoll / rider data (mActor+0x570 ...).
    void sub_7100E63424();
    // Placeholder names (declared only: no callers identified yet; lane4 s28).
    // 0x7100e63900: sets bit 0x80 of _8 if bit 0x20 is set.
    void sub_7100E63900();
    // 0x7100e6314c: keeps the larger value for rank 1 or 2 (only the id for the larger value is stored).
    void sub_7100E6314C(Rank rank, f32 value, u32 id);

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
    /* 15 */ virtual void m15(f32 a, f32 b) {}
    /* 16 */ virtual void m16(f32 value) {}

    /* 0x008 */ sead::Atomic<u32> _8 = 0;  // flags
    /* 0x010 */ ksys::act::Actor* mActor = nullptr;
    /* 0x018 */ S1 _18;
    /* 0x0a0 */ S2 _a0;
    /* 0x130 */ u32 _130 = 0;
    /* 0x134 */ u32 _134 = 0;
    /* 0x138 */ f32 _138 = 0;
    /* 0x13c */ f32 _13c = 0;
    /* 0x140 */ u32 _140 = 0;
    /* 0x144 */ u32 _144 = 0;
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
    // SEAD_ENUM in the original (stack round trip): the gear of the rider's AS controller (`_18._b`, `_18._9` when 0).
    SEAD_ENUM(Gear, _0, _1, _2, _3, _4, _5, _6, _7)

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
    /* 19 */ virtual s32 m19() { return 0; }
    /* 20 */ virtual void m20(s32 a) {}
    /* 21 */ virtual s32 m21() { return 0; }
    /* 22 */ bool m22(Unk8 a1) override;
    // callers and overrides copy the result through the stack: probably a SEAD_ENUM
    /* 23 */ virtual Gear m23();
    /* 24 */ virtual void m24();
    /* 25 */ bool m25() override { return false; }
    /* 26 */ f32 m26() override { return 0.0f; }
    /* 27 */ f32 m27() override { return 0.0f; }
    /* 28 */ f32 m28() override { return 0.0f; }
    /* 29 */ virtual void m29(f32 a) {}
    /* 30 */ virtual f32 m30(f32 delta) { return m31(); }
    /* 31 */ virtual f32 m31() { return 1.0f; }
    /* 32 */ virtual f32 m32() { return 0.0f; }
    /* 33 */ virtual f32 m33() { return 0.0f; }
    /* 34 */ virtual f32 m34() { return 0.0f; }
    /* 35 */ virtual f32 m35() { return 0.0f; }
    /* 36 */ virtual f32 m36() { return 0.0f; }
    /* 37 */ virtual f32 m37() { return 0.0f; }
    /* 38 */ virtual f32 m38() { return 0.0f; }
    /* 39 */ virtual HorseReins* m39() { return nullptr; }
    /* 40 */ virtual HorseReins* m40();
    /* 41 */ virtual HorseReins* m41() { return nullptr; }
    /* 42 */ void m42(int a1) override;
    /* 43 */ void m43() override {}
    /* 44 */ virtual bool m44();

    // 0x7100e7ef1c (placeholder name): emits the xlink events "Attached" and "mc_HorseSoothe" on the actor.
    void sub_7100E7EF1C();

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
    /* 0x278 */ u8 _278 = 0;
    /* 0x279 */ s8 _279 = 0;  // LynelRodeo::calc_ reads it with ldrsb (finished when negative)
};
KSYS_CHECK_SIZE_NX150(Rideable, 0x280);

// 0x7100e80d18 (placeholder name): Rideable::sub_7100E7EF1C for the rideable of `actor` while its state (_c) is 1.
void sub_7100E80D18(ksys::act::Actor* actor);

// Ridden anim-driven movement helpers (TU 0x7100e7f25c-, after Rideable's RTTI functions).
// 0x7100e7f318: applies the AS anim-driven movement of `as_list` to `controller` (`scale` = 1 / the
// rider AS speed). Not decompiled yet.
void sub_7100E7F318(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller, f32 scale);
// 0x7100e7f4fc: variant of sub_7100E7F318 (anim-driven movement along the controller's forward
// direction; GetUpMoveAnmDriven::calc_ passes scale 1). Not decompiled yet.
void sub_7100E7F4FC(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller, f32 scale);
// 0x7100e7f698: sub_7100E7F318 with the scale from `rideable` (_18._24); with bit 2 of
// rideable->_8 set it resets the controller (sub_7100F5EDD8(1) / sub_7100F5EDE0(0)) instead.
void sub_7100E7F698(RideableBase* rideable, ksys::as::ASList* as_list,
                    ksys::phys::CharacterController* controller);
// 0x7100e7f6fc: another anim-driven movement variant (ForkAnimDriveFreeMoving::calc_ passes scale 1).
// Not decompiled yet.
void sub_7100E7F6FC(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller, f32 scale);

// 0x7100e816e4: picks a random reachable destination for `actor` around the rider position `pos`
// (HorseRandomMoveAction::enter_; the float parameters are its static params, not decompiled yet).
bool sub_7100E816E4(f32 dir_range_rad, f32 radius_limit, f32 dir_random, f32 fwd_dist_coef,
                    f32 reject_dist_ratio, ksys::act::Actor* actor, const sead::Vector3f& pos);

}  // namespace uking::act

// 0x7100e7f25c (declaration only): transfers the actor's AS bank to `list`.
// The original source owner is unknown; keep a global placeholder instead of assigning a class.
void sub_7100E7F25C(ksys::as::ASList* list, ksys::act::Actor* actor, s32 slot, s32 bank,
                   s32 other_bank);
