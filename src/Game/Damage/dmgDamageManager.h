#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

// CSV: DamageMgr (vtable 0x710244ddf8, 57 slots; ctor 0x71006d23e0). RTTI static 0x71025ae600.
// TODO: incomplete. Size 0x230 (the ctor's last store is at 0x228; Horse embeds one at 0xd20
// followed by a member at 0xf50).
class DamageManager : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageManager, DamageManagerBase)
public:
    explicit DamageManager(ksys::act::Actor* actor);

    u8 _68[0x74 - 0x68];
    s32 _74;  // Horse::loadReduceAncientEnemyDamageInfo
    u8 _78[0x230 - 0x78];
};
KSYS_CHECK_SIZE_NX150(DamageManager, 0x230);

}  // namespace uking::dmg
