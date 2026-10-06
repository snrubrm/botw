#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_7102357210.h"
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
    virtual ~Unk_71025ae680();

    // FIXME: figure out return types, parameters and names
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual bool m8(const ksys::Message& message);
    virtual bool m9();
    virtual void m10();
    virtual void m11(bool enable);
    virtual void m12();
    virtual void m13(int index);  // DemoEnemyReset::enter_ calls it for 0..11

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
    /* 0x1c */ u32 _1c;
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

    void m7() override;
    bool m8(const ksys::Message& message) override;

    /* 0x020 */ u8 _20[0x38 - 0x20];
    /* 0x038 */ f32 _38;  // FlyingCharacterFreezeDie: 0 in enter_, 1 in leave_
    /* 0x03c */ u8 _3c[0x88 - 0x3c];
    // Listener (message 0x800009b); PriestBossShadowCloneEnemyRoot::enter_ resets it (x()).
    /* 0x088 */ Unk_710235a0c0 _88;
    /* 0x0c0 */ u8 _c0[0x138 - 0xc0];
    /* 0x138 */ u8 _138;  // flags: 1 burn, 2 ice, 4 electric invalidated (behavior InvalidateCondition)
    // (sizeof is 0x140 via tail padding: Player's derived object stores members at 0x13c.)
};
KSYS_CHECK_SIZE_NX150(Unk_710244dd20, 0x140);

// Placeholder name (ctor 0x8502cc; own vtable, GOT 0x2592e28). The Unk_710244dd20 subclass embedded in
// Player at 0x2550 (Player::m159). Size 0x150.
// TODO: incomplete.
class Unk_71008502cc : public Unk_710244dd20 {
public:
    explicit Unk_71008502cc(ksys::act::Actor* actor);

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
    /* 0x20 */ u8 _20[0x28 - 0x20];
    /* 0x28 */ u8 _28;  // flags (BeeSwarmRoot::enter_ sets bit 0)
    /* 0x29 */ u8 _29[0x68 - 0x29];
};
KSYS_CHECK_SIZE_NX150(Unk_710244ff68, 0x68);

}  // namespace uking::act
