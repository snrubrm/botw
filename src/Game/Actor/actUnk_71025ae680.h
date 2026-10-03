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
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13(int index);  // DemoEnemyReset::enter_ calls it for 0..11

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

    void m7() override;
    bool m8(const ksys::Message& message) override;

    /* 0x020 */ u8 _20[0x38 - 0x20];
    /* 0x038 */ f32 _38;  // FlyingCharacterFreezeDie: 0 in enter_, 1 in leave_
    /* 0x03c */ u8 _3c[0x88 - 0x3c];
    // Listener (message 0x800009b); PriestBossShadowCloneEnemyRoot::enter_ resets it (x()).
    /* 0x088 */ Unk_710235a0c0 _88;
    /* 0x0c0 */ u8 _c0[0x138 - 0xc0];
    /* 0x138 */ u8 _138;  // flags: 1 burn, 2 ice, 4 electric invalidated (behavior InvalidateCondition)
    /* 0x139 */ u8 _139[0x140 - 0x139];
};
KSYS_CHECK_SIZE_NX150(Unk_710244dd20, 0x140);

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
