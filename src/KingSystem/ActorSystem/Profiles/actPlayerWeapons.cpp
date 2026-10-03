#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace ksys::act {

// Separate TU from actPlayer.cpp: Player::m273 / m274 / m275 call these out of line in the original
// (a same-TU definition is inlined as a constant).
s32 Player::playerWeapons_return0() {
    return 0;
}

s32 Player::playerWeapons_return1() {
    return 1;
}

s32 Player::playerWeapons_return2() {
    return 2;
}

}  // namespace ksys::act
