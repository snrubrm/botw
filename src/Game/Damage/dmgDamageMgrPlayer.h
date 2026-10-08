#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManager.h"

namespace uking::dmg {

// Name from the CSV (DamageMgrPlayer::*; vtable 0x710246aa50, ctor 0x71008515dc, TU 0x7100851550 - 0x7100852400; RTTI
// static 0x71025c94e0). The damage manager of the Player (DamageManager at 0x0 + the members below). Size 0x238.
// Only the layout, the ctor and the RTTI are declared: the overrides (slots 0-3 [RTTI, D1 / D0 inline the whole
// DamageManager destructor chain], 15, 20, 22, 47, 50-56) are not decompiled.
class DamageMgrPlayer : public DamageManager {
    SEAD_RTTI_OVERRIDE(DamageMgrPlayer, DamageManager)
public:
    explicit DamageMgrPlayer(ksys::act::Actor* actor);

    s32 m52() override;

    // Set by Player::sub_7100884578 (PlayerIce / PlayerElectric leave_) to the unnamed .rodata int 30.
    /* 0x22c */ f32 _22c;
    /* 0x230 */ u16 _230;
    /* 0x232 */ u8 _232;
};
KSYS_CHECK_SIZE_NX150(DamageMgrPlayer, 0x238);

}  // namespace uking::dmg
