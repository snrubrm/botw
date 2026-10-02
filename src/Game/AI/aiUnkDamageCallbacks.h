#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageCallback.h"

// Unnamed damage callback classes with their own RTTI, embedded in many AI/Action/Behavior classes.
// Their virtual functions (call, checkDerivedRuntimeTypeInfo, getRuntimeTypeInfo, D0) all live in
// one translation unit (0x7100747a0c-0x710074a950), so `call` is the key function and is defined
// out of line in aiUnkDamageCallbacks.cpp. Placeholder names are the vtable addresses.

// vtable 0x71024518c8
class Unk_71024518c8 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024518c8, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451938
class Unk_7102451938 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451938, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 1;
};

// vtable 0x7102451970
class Unk_7102451970 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451970, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x71024519a8 (functions at 0x71007484c8..0x7100748768; `call` reads its last argument as a
// pointer to an object of an unknown RTTI class, so it is not defined yet). Embedded in GuardNearTarget,
// InvincibleHiddenOctarock, StoneOctarockWait and the SetAllNoDamageDCCallback behavior.
class Unk_71024519a8 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024519a8, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = true;
    bool _25 = true;
};

// vtable 0x71024519e0
class Unk_71024519e0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024519e0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451a18
class Unk_7102451a18 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451a18, uking::dmg::DamageCallback)
public:
    explicit Unk_7102451a18(ksys::act::Actor* actor) : mActor(actor) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    ksys::act::Actor* mActor;
};

// vtable 0x7102451a50 (`call` 0x7100748ae8 is not defined yet: it calls two unnamed functions).
// Embedded in Horse (0x1170) and the SetIgnoreHorseDamage behavior.
class Unk_7102451a50 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451a50, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451a88
class Unk_7102451a88 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451a88, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451ac0
class Unk_7102451ac0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451ac0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    u32 _24 = 0;
};

// vtable 0x7102451bd8
class Unk_7102451bd8 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451bd8, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451c10
class Unk_7102451c10 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451c10, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451c98
class Unk_7102451c98 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451c98, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451d78
class Unk_7102451d78 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451d78, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 0;
};

// vtable 0x71024500d8 (ChuchuRoot). Its functions live in another translation unit (0x71006f6284..),
// so `call` is only declared here.
class Unk_71024500d8 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024500d8, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102451ba0 (BackAttackEnemyBattle and ~30 actions). `call` needs ASList::x / isSlowTimeMaybe and an
// unnamed DamageManager method (0x71006d8534), so it is only declared.
class Unk_7102451ba0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451ba0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
};
