#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageMgrWeapon.h"

namespace uking::dmg {

DamageMgrBow::DamageMgrBow(ksys::act::Actor* actor) : DamageMgrSword(actor) {}

bool DamageMgrBow::m54() {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    return weapon && (weapon->_af8._0 | 1) == 7 && weapon->_d58[0] == 0;
}

}  // namespace uking::dmg
