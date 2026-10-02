#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::dmg {

// CSV: DamageMgr (vtable 0x710244ddf8, 57 slots; ctor 0x71006d23e0). RTTI static 0x71025ae600.
// TODO: incomplete. Size 0x230 (the ctor's last store is at 0x228; Horse embeds one at 0xd20
// followed by a member at 0xf50).
class DamageManager : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageManager, DamageManagerBase)
public:
    explicit DamageManager(ksys::act::Actor* actor);

    // 0x71006d69f8 (not decompiled): the rigid body hit by the current damage (by damage kind
    // _5c: 2 / 6 via sub_71007A255C, 4 via the actor's +0x708 object), or null.
    ksys::phys::RigidBody* sub_71006D69F8();

    u8 _68[0x74 - 0x68];
    s32 _74;  // Horse::loadReduceAncientEnemyDamageInfo
    u8 _78[0x8c - 0x78];
    s32 _8c;  // WeakPointRoot::m35
    u8 _90[0x210 - 0x90];
    // 0x210-0x22c: zeroed by the ctor (0x210 and 0x214 with one 8-byte store).
    u32 _210;
    u16 _214;
    // Flags (ctor: 9). AI code tests bit 1 (`_216.isOn(2)`, ~15 functions).
    sead::BitFlag16 _216;
    u16 _218;
    u64 _220;
    u32 _228;
};
KSYS_CHECK_SIZE_NX150(DamageManager, 0x230);

}  // namespace uking::dmg
