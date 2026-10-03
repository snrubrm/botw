#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (OptionalWeapon::m2 / m3 = its RTTI virtuals at 0x7100ef2420 / 0x7100ef2538, between
// the WeaponBase functions; the namespace is a guess). RTTI static 0x71025b1968: a direct child of Actor
// (the static is initialised with the Derive<Actor> vtable), used by EquipedOptionalWeaponAction /
// OptionalWeaponAI. WeaponBase::m162 / m163 return the OptionalWeapon linked at WeaponBase +0x958.
// Not decompiled: only the RTTI is declared.
class OptionalWeapon : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(OptionalWeapon, ksys::act::Actor)
public:
    ~OptionalWeapon() override;

    // 0x7100ef1adc (CSV OptionalWeaponMaybe::x; called when a WeaponBase drops its optional weapon).
    void sub_7100EF1ADC();
};

}  // namespace uking::act
