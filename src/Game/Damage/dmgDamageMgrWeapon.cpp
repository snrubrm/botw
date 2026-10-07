#include "Game/Damage/dmgDamageMgrWeapon.h"

namespace uking::dmg {

DamageMgrWeapon::DamageMgrWeapon(ksys::act::Actor* actor) : DamageManagerBase(actor) {
    mIsOwnedByPlayer = false;
}

}  // namespace uking::dmg
