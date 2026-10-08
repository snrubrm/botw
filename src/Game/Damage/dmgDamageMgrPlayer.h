#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManager.h"

namespace uking::dmg {

// Name from the CSV (DamageMgrPlayer::*; vtable 0x710246aa50, ctor 0x71008515dc, TU 0x7100851550 - 0x7100852400; RTTI
// static 0x71025c94e0). The damage manager of the Player (DamageManager at 0x0 + the members below). Size 0x238.
// Only the layout, the ctor and the RTTI are declared: the overrides (slots 0-3 [RTTI, D1 / D0 inline the whole
// DamageManager destructor chain], 15, 20, 22, 47, 50-56) are not decompiled.
class DamageMgrPlayer : public DamageManager {
public:
    // Replaces SEAD_RTTI_OVERRIDE: the original's checkDerivedRuntimeTypeInfoStatic
    // (0x710085269c) is a flat comparison against the four typeinfos of the inheritance
    // chain (Player, Manager, ManagerBase, ManagerBase_UnknownBase1), not the chained
    // per-class form the macro generates.
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<DamageManager> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(
        const sead::RuntimeTypeInfo::Interface* typeInfo);
    bool checkDerivedRuntimeTypeInfo(
        const sead::RuntimeTypeInfo::Interface* typeInfo) const override;
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;

    void resetDamage() override;
    void m22() override;
    s32 m53() override;
    bool m56() override;

    // 0x71006d276c (in the DamageManager TU range; called only by applyDamage):
    // reset the damage indices, flags and direction. Placeholder name.
    void x();
    explicit DamageMgrPlayer(ksys::act::Actor* actor);

    s32 m52() override;
    void m55() override;

    // Set by Player::sub_7100884578 (PlayerIce / PlayerElectric leave_) to the unnamed .rodata int 30.
    /* 0x22c */ f32 _22c;
    /* 0x230 */ u8 _230 = 0;
    // 0x7100852060 (m55): skip the base handling while this is set.
    /* 0x231 */ bool _231 = false;
    /* 0x232 */ u8 _232 = 0;
};
KSYS_CHECK_SIZE_NX150(DamageMgrPlayer, 0x238);

}  // namespace uking::dmg
