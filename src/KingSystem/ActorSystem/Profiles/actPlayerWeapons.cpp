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

// NON_MATCHING: our build merges the two identical branches and tail-calls hasProc; the original keeps both.
// Placeholder name: whether weapon slot 2 holds a weapon. The original compares _d30 with the equipment type 3
// name first; both outcomes make the same check.
bool Player::sub_7100881EDC() {
    if (_d30 == getEquipmentTypeName(3))
        return getWeapons()->mWeapons[playerWeapons_return2()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return2()].link.hasProc();
}

// NON_MATCHING: as sub_7100881EDC (two identical branches merged in our build).
// Placeholder name: whether weapon slot 1 holds a weapon, after comparing _d30 with the equipment type 1 name.
bool Player::sub_7100888294() {
    if (_d30 == getEquipmentTypeName(1))
        return getWeapons()->mWeapons[playerWeapons_return1()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return1()].link.hasProc();
}

// NON_MATCHING: as sub_7100881EDC (two identical branches merged in our build).
// Placeholder name: whether weapon slot 0 holds a weapon, after comparing _d30 with the equipment type 1 name.
bool Player::sub_71008921A8() {
    if (_d30 == getEquipmentTypeName(1))
        return getWeapons()->mWeapons[playerWeapons_return0()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return0()].link.hasProc();
}

}  // namespace ksys::act
