#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

// vtable 0x71023cee50 (DamageMgrNPC::_68): sends message 0x80000b5 (m2 at 0x71002c9ff4, declaration only).
class Unk_71023cee50 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override;
};

// Name from the CSV (DamageMgrNPC::*; vtable 0x71023ceca0, ctor 0x71002c9024, TU 0x71002c9024 -
// 0x71002ca000). The damage manager embedded in NPC (+0xda0). Size 0x90. Only the layout and the
// constructor are declared; the overrides (RTTI, slots 18-41 at 0x71002c909c, 0x71002c9670 ...) are
// not decompiled.
class DamageMgrNPC : public DamageManagerBase {
public:
    explicit DamageMgrNPC(ksys::act::Actor* actor);

    // Slot 28 getAttackPos (0x71002c9670; lane4 s64): the direction of the damage by kind: 0 the first contact record's vector, 2 the
    // actor's impulse link vector (zero without one), 3 the direction `_80` (else minus the actor's x axis), others false.
    bool getAttackPos(sead::Vector3f* out) override;

    /* 0x68 */ Unk_71023cee50 _68;
    /* 0x80 */ sead::Vector3f _80;
};
KSYS_CHECK_SIZE_NX150(DamageMgrNPC, 0x90);

}  // namespace uking::dmg
