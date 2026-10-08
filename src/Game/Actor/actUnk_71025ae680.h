#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class Message;
namespace act {
class Actor;
}  // namespace act
}  // namespace ksys

namespace ksys::res {
class DamageParam;
}

namespace uking::act {

// Placeholder name (RTTI static 0x71025ae680; vtable 0x710244e820, 14 slots: RTTI, dtor, 10 more).
// Returned by DynamicActor vtable slot 159 (Enemy::_e78, created by Enemy vtable slot 178; Player
// and Horse embed one at 0x2550 / 0x1028). Derived classes: vtable 0x710244edc0 (RTTI 0x71025aea10,
// size 0x70, built inline by Enemy slot 178) and vtable 0x710244dd20 (size 0x140, ctor
// 0x71006cef7c).
// TODO: incomplete.
class Unk_71025ae680 {
    SEAD_RTTI_BASE(Unk_71025ae680)
public:
    // 2026-10-07: the actor controller factories initialise this common prefix.
    explicit Unk_71025ae680(ksys::act::Actor* actor) : _8(0), _a(0), _10(actor), _18(-1) {}
    virtual ~Unk_71025ae680();

    // FIXME: figure out return types, parameters and names
    virtual bool m4() { return true; }
    virtual void m5() {}
    virtual void m6();
    virtual void m7();
    virtual bool m8(const ksys::Message& message) { return false; }
    virtual bool m9() { return false; }
    virtual void m10() {}
    virtual void m11(bool enable) {}
    virtual void m12(int index) {}
    virtual void m13(int index) {}  // DemoEnemyReset::enter_ calls it for 0..11

    // 0x71006df750 (placeholder name): `m13(11)`.
    void sub_71006DF750();
    // 0x71006df67c (lane4 s64; placeholder name): adds `value` to the actor's life (if it has one), clamped to [0, max life].
    void sub_71006DF67C(s32 value);
    // 0x71006df6ec (placeholder name): `m13(7)`, `m13(8)`, `m13(9)`, `m13(10)`.
    void sub_71006DF6EC();

    // 0x71006dfa04 (not decompiled): if `enable` changes bit 0 of `_a`, calls m13(0..11) first when enabling,
    // then m11(enable), then updates the bit (behavior Invincible).
    void sub_71006DFA04(bool enable);

    // 0x71006ef05c / 0x71006eefb4 (declared only, lane5 s6; 0x71006ef05c resets everything, 0x71006eefb4 resets the
    // range [a, b]): called by SwarmChemicalDamaged::sub_71002831E4.
    void sub_71006EF05C();
    void sub_71006EEFB4(s32 a, s32 b);

    // 0x71006df5a4: resolves the actor damage resource.
    ksys::res::DamageParam* sub_71006DF5A4();

    /* 0x08 */ sead::BitFlag16 _8;  // tested by DynamicActor slots 151 (bit) and 152 (mask)
    /* 0x0a */ u8 _a;
    /* 0x10 */ ksys::act::Actor* _10;
    /* 0x18 */ s32 _18;
};
KSYS_CHECK_SIZE_NX150(Unk_71025ae680, 0x20);

// Placeholder name (vtable 0x710244dd20; ctor 0x71006cef7c, size 0x140). Horse::_1028 and the
// second kind of object created by Enemy vtable slot 178. Has a second base (vtable 0x710244dd20 +
// 0xc8) at 0x20.
// TODO: incomplete.
class Unk_710244dd20 : public Unk_71025ae680 {
    SEAD_RTTI_OVERRIDE(Unk_710244dd20, Unk_71025ae680)
public:
    explicit Unk_710244dd20(ksys::act::Actor* actor);

    // 0x71006d1d48 / 0x71006d1d7c / 0x71006d1da0: damage-resource ice/electric properties.
    f32 sub_71006D1D48();
    bool sub_71006D1D7C();
    bool sub_71006D1DA0();
    // 0x71006d22b4 (lane4 s64; placeholder name): whether bit `bit` of `_139` is set.
    bool sub_71006D22B4(s32 bit) const;

    void m7() override;
    bool m8(const ksys::Message& message) override;

    /* 0x01c */ u8 _1c[4];  // opaque alignment gap before the secondary interface at +0x20
    /* 0x020 */ u8 _20[0x38 - 0x20];
    /* 0x038 */ f32 _38;  // FlyingCharacterFreezeDie: 0 in enter_, 1 in leave_
    /* 0x03c */ u8 _3c[0x88 - 0x3c];
    // Listener (message 0x800009b); PriestBossShadowCloneEnemyRoot::enter_ resets it (x()).
    /* 0x088 */ Unk_710235a0c0 _88;
    /* 0x0c0 */ u8 _c0[0xd0 - 0xc0];
    // Set by Player's 0x710088588c / 0x710088592c (ice / electric; the matching `_138` bits 2 / 4 say whether it is 0).
    /* 0x0d0 */ f32 _d0;
    /* 0x0d4 */ f32 _d4;
    /* 0x0d8 */ u8 _d8[0x138 - 0xd8];
    /* 0x138 */ u8 _138;  // flags: 1 burn, 2 ice, 4 electric invalidated (behavior InvalidateCondition)
    /* 0x139 */ sead::BitFlag8 _139;
    // (sizeof is 0x140 via tail padding: Player's derived object stores members at 0x13c.)
};
KSYS_CHECK_SIZE_NX150(Unk_710244dd20, 0x140);

// Placeholder name (ctor 0x8502cc; own vtable, GOT 0x2592e28). The Unk_710244dd20 subclass embedded in
// Player at 0x2550 (Player::m159). Size 0x150.
// TODO: incomplete.
class Unk_71008502cc : public Unk_710244dd20 {
public:
    explicit Unk_71008502cc(ksys::act::Actor* actor);

    // 0x7100850ce4 / 0x7100850cf4 (lane4 s64; placeholder names): `_8` has a bit of 0x3 / 0x587 set.
    bool sub_7100850CE4() const;
    bool sub_7100850CF4() const;

    /* 0x13c */ u32 _13c;
    /* 0x140 */ u32 _140;
    /* 0x144 */ u32 _144;
    /* 0x148 */ u32 _148;
};
KSYS_CHECK_SIZE_NX150(Unk_71008502cc, 0x150);

// Placeholder name (vtable 0x710244ff68; no out-of-line ctor: built inline by Swarm::m178, size
// 0x68). The unit-controller object of the swarm actors (Swarm::_e78 / m159).
// TODO: incomplete.
class Unk_710244ff68 : public Unk_71025ae680 {
    SEAD_RTTI_OVERRIDE(Unk_710244ff68, Unk_71025ae680)
public:
    explicit Unk_710244ff68(ksys::act::Actor* actor)
        : Unk_71025ae680(actor), _1c(-1), _20(-1), _24(-1), _28(0) {}
    ~Unk_710244ff68() override;

    bool m4() override { return true; }
    void m5() override {
        _8.makeAllZero();
        _28 = 0;
    }
    void m7() override { Unk_71025ae680::m7(); }
    bool m8(const ksys::Message& message) override;
    void m10() override;
    void m11(bool enable) override;
    void m12(int index) override;
    void m13(int index) override { _8.resetBit(index); }

    // 2026-10-07: factories of sibling controllers reuse the common prefix's tail padding
    // for different types; the swarm's three condition indices start here.
    /* 0x1c */ s32 _1c;
    /* 0x20 */ s32 _20;  // SwarmChemicalDamaged::sub_7100283004 (placeholder names)
    /* 0x24 */ s32 _24;
    /* 0x28 */ u8 _28;  // flags (BeeSwarmRoot::enter_ sets bit 0)
    /* 0x30 */ Unk_710235a0c0 _30;
};
KSYS_CHECK_SIZE_NX150(Unk_710244ff68, 0x68);

// 2026-10-07: GiantEnemy's controller factory and its timer/effect readers establish this layout.
class Unk_710244ebc8 : public Unk_71025ae680 {
    SEAD_RTTI_OVERRIDE(Unk_710244ebc8, Unk_71025ae680)
public:
    explicit Unk_710244ebc8(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}
    ~Unk_710244ebc8() override;
    bool m4() override { return true; }
    void m5() override { _8.makeAllZero(); }
    void m7() override { Unk_71025ae680::m7(); }
    bool m8(const ksys::Message& message) override;
    void m10() override;
    void m12(int index) override;
    void m13(int index) override;

    /* 0x1c */ f32 _1c = 0;
    /* 0x20 */ Unk_71012419b4 _20;
    /* 0x40 */ Unk_710235a0c0 _40;
};
KSYS_CHECK_SIZE_NX150(Unk_710244ebc8, 0x78);

// 2026-10-07: LastBoss's factory places the message listener before its paired effect handles.
class Unk_710244eb48 : public Unk_71025ae680 {
    SEAD_RTTI_OVERRIDE(Unk_710244eb48, Unk_71025ae680)
public:
    explicit Unk_710244eb48(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}
    ~Unk_710244eb48() override;
    bool m4() override { return true; }
    void m5() override;
    // 0x71006e252c (lane4 s64; placeholder name): m5's body, called by LastBoss code.
    void sub_71006E252C();
    void m7() override { Unk_71025ae680::m7(); }
    bool m8(const ksys::Message& message) override;
    void m10() override;
    // Placeholder (0x71006e264c, declared only): needs sub_71006DF5CC + eft/xlink decls.
    void sub_71006E264C();

    /* 0x1c */ bool _1c = false;
    /* 0x20 */ Unk_710235a0c0 _20;
    /* 0x58 */ Unk_71012419b4 _58;
};
KSYS_CHECK_SIZE_NX150(Unk_710244eb48, 0x78);

// 2026-10-07: SiteBoss's factory uses the same member types as the LastBoss controller.
class Unk_710244fee8 : public Unk_71025ae680 {
    SEAD_RTTI_OVERRIDE(Unk_710244fee8, Unk_71025ae680)
public:
    explicit Unk_710244fee8(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}
    ~Unk_710244fee8() override;
    bool m4() override { return true; }
    void m5() override;
    // 0x71006ee354 (lane4 s64; placeholder name): m5's body, called by SiteBoss code.
    void sub_71006EE354();
    void m7() override { Unk_71025ae680::m7(); }
    bool m8(const ksys::Message& message) override;
    void m10() override;
    // Placeholder (0x71006ee474, declared only): the fee8 twin of sub_71006E264C.
    void sub_71006EE474();

    /* 0x1c */ bool _1c = false;
    /* 0x20 */ Unk_710235a0c0 _20;
    /* 0x58 */ Unk_71012419b4 _58;
};
KSYS_CHECK_SIZE_NX150(Unk_710244fee8, 0x78);

// 0x71006dfb58 (placeholder name): bit 20 of the flags of the world chemical element holder (ChemicalMgr::_ae8);
// false without one.
bool sub_71006DFB58();

}  // namespace uking::act
