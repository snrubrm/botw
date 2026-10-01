#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::ai {

// vtable 0x71024519a8 (functions at 0x71007484c8..0x7100748768). Embedded in GuardNearTarget,
// InvincibleHiddenOctarock, StoneOctarockWait and the SetAllNoDamageDCCallback behavior.
class Unk_71024519a8 : public dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71024519a8, dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = true;
    bool _25 = true;
};

}  // namespace uking::ai
