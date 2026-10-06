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
// Placeholder (the object at DamageManager::_220; only the field read by sub_71006D8534).
struct DamageManagerUnk220 {
    u8 _0[0x10];
    s32 _10;
};

class DamageManager : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageManager, DamageManagerBase)
public:
    explicit DamageManager(ksys::act::Actor* actor);
    void preDelete1() override;

    // 0x71006d69f8 (not decompiled): the rigid body hit by the current damage (by damage kind
    // _5c: 2 / 6 via sub_71007A255C, 4 via the actor's +0x708 object), or null.
    ksys::phys::RigidBody* sub_71006D69F8();

    // 0x71006d8de8 (lane3 s36; declared only): the damage factor (1.0; 2.0 if the attacker's weapon is a
    // Pikohan / one-hit obliterator). Placeholder name.
    f32 sub_71006D8DE8();

    // 0x71006d8534 (lane1 s22): `_220 ? _220->_10 : 0`. Placeholder name.
    s32 sub_71006D8534() const;

    s32 _68;  // WolfLinkRoot::enter_
    u8 _6c[0x70 - 0x6c];
    s32 _70;  // current shield guard power (PlayerOrEnemy::m160)
    s32 _74;  // Horse::loadReduceAncientEnemyDamageInfo
    u8 _78[0x8c - 0x78];
    s32 _8c;  // WeakPointRoot::m35
    u8 _90[0x210 - 0x90];
    // 0x210-0x22c: zeroed by the ctor (0x210 and 0x214 with one 8-byte store).
    u16 _210;
    u16 _212;
    u16 _214;
    // Flags (ctor: 9). AI code tests bit 1 (`_216.isOn(2)`, ~15 functions).
    sead::BitFlag16 _216;
    u16 _218;
    DamageManagerUnk220* _220;
    u32 _228;
};
KSYS_CHECK_SIZE_NX150(DamageManager, 0x230);

}  // namespace uking::dmg

// 0x71006d28ac: actor attack info or a non-dummy damage resource requires a damage manager.
// Declaration only; namespace unknown.
bool sub_71006D28AC(ksys::act::Actor* actor);
// CSV name at 0x71006d28fc; declaration only, namespace unknown. Original allocates 0x230
// and calls DamageManager's actual 0x71006d23e0 constructor, returning that object or null.
uking::dmg::DamageManager* gameObjectInitField(ksys::act::Actor* actor, sead::Heap* heap);
