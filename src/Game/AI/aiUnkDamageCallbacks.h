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

// vtable 0x71024519e0
class Unk_71024519e0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024519e0, uking::dmg::DamageCallback)
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
