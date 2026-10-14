#include "Game/Damage/dmgDamageMgrWeapon.h"

namespace uking::act {

DamageMgrWeapon::DamageMgrWeapon(ksys::act::Actor* actor) : DamageManagerBase(actor) {
    mIsOwnedByPlayer = false;
}

}  // namespace uking::act
