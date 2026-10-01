#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageCallback.h"

// Unnamed damage callback class with its own RTTI (vtable 0x7102451ba0), embedded in many attack actions
// (FallAttack, PreAttack, JumpTackle, PunchAttack, BackStepBase, ...). Its virtual functions live in the
// damage callback TU 0x7100747a0c-0x710074a950 together with the other Unk_71024518c8.. classes:
// call 0x7100749720 (key function, not decompiled yet: ASList::x + unnamed 0x71011638dc), checkDerived
// 0x7100749824, getRuntimeTypeInfo 0x71007498f0, D0 0x710074994c; D1 is DamageCallback's D2.
class Unk_7102451ba0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451ba0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
};
