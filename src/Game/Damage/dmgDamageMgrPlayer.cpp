#include "Game/Damage/dmgDamageMgrPlayer.h"

namespace uking::dmg {

s32 DamageMgrPlayer::m52() {
    return 12;
}

void DamageMgrPlayer::m55() {
    if (_231)
        return;
    DamageManager::m55();
}

}  // namespace uking::dmg
