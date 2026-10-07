#pragma once

#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

// Names from the CSV (DamageMgrWeapon / DamageMgrSword / DamageMgrBow / DamageMgrShield::*). The damage managers of the
// Weapon actor (allocated by Weapon::init1: DamageMgrBow for bows, DamageMgrShield for shields, DamageMgrSword
// otherwise; each is 0x78 bytes). Like DamageManager, they add virtual slots 50 and up (m50 sets the damage from the
// life multiplier scaled by the argument, m51 returns it, m52 / m53 are flags).
//
// Vtables: Weapon 0x7102357b40, Sword 0x71023d2750, Bow 0x71023556e0, Shield 0x71023cfd10.
// RTTI statics: Weapon 0x71025ae5a0, Sword 0x71025ae590, Bow 0x71025ae580, Shield 0x71025b6e88.
class DamageMgrWeapon : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageMgrWeapon, DamageManagerBase)
public:
    explicit DamageMgrWeapon(ksys::act::Actor* actor);

    virtual void m50(f32 scale) {}
    virtual s32 m51() { return 1; }
    virtual bool m52() { return false; }
    virtual bool m53() { return false; }
};
KSYS_CHECK_SIZE_NX150(DamageMgrWeapon, 0x68);

class DamageMgrSword : public DamageMgrWeapon {
    SEAD_RTTI_OVERRIDE(DamageMgrSword, DamageMgrWeapon)
public:
    explicit DamageMgrSword(ksys::act::Actor* actor);

    s32 getNumCallbacks() override { return 2; }
    void resetDamage() override;
    void m22() override;
    bool getPosition(sead::Vector3f* out) override;
    bool getAttackPos(sead::Vector3f* out) override;
    ksys::phys::MaterialMask* m33() override;

    void m50(f32 scale) override;
    s32 m51() override { return mDamageFromLife; }
    bool m52() override { return _70; }
    virtual bool m54();

    /* 0x68 */ s32 mDamageFromLife;  // WeaponModifierInfo::getLifeMultiplier() (scaled by m50)
    /* 0x6c */ s32 _6c;  // the WeaponCommon IsBlunt-like flag of the weapon (resetDamage)
    /* 0x70 */ bool _70;

private:
    // 0x71002f267c (CSV DamageMgrWeapon::x_0): fills the damage values of a hit by the weapon.
    bool sub_71002F267C(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40);
};
KSYS_CHECK_SIZE_NX150(DamageMgrSword, 0x78);

class DamageMgrBow : public DamageMgrSword {
    SEAD_RTTI_OVERRIDE(DamageMgrBow, DamageMgrSword)
public:
    explicit DamageMgrBow(ksys::act::Actor* actor);

    bool getPosition(sead::Vector3f* out) override { return false; }
    bool getAttackPos(sead::Vector3f* out) override { return false; }
    ksys::phys::MaterialMask* m33() override { return nullptr; }
    bool m54() override;
};
KSYS_CHECK_SIZE_NX150(DamageMgrBow, 0x78);

class DamageMgrShield : public DamageMgrWeapon {
    SEAD_RTTI_OVERRIDE(DamageMgrShield, DamageMgrWeapon)
public:
    explicit DamageMgrShield(ksys::act::Actor* actor);
    ~DamageMgrShield() override;

    s32 getNumCallbacks() override { return 1; }
    void resetDamage() override;
    void m22() override;

    void m50(f32 scale) override;
    s32 m51() override { return mDamageFromLife; }
    bool m53() override { return _74; }

    /* 0x68 */ f32 _68;  // timers advanced with ksys::Timer::update
    /* 0x6c */ f32 _6c;
    /* 0x70 */ s32 mDamageFromLife;
    /* 0x74 */ bool _74;

private:
    // 0x71002ceaf4 / 0x71002ced6c (CSV DamageMgrShield::shieldSurfDamageLogic / shieldDamageLogic): fill the damage
    // values of a hit while surfing / blocking with the shield.
    bool shieldSurfDamageLogic(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40);
    bool shieldDamageLogic(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54, s32* f40);
};
KSYS_CHECK_SIZE_NX150(DamageMgrShield, 0x78);

}  // namespace uking::dmg
