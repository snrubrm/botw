#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Placeholder name (CSV: PlayerArmors::x_3 / x_4 / x_5 and unnamed methods in the TU
// 0x7100e2c1fc-0x7100e31570): the player's armor state, embedded in Player at +0x23e0 (0x170
// bytes; Actor::getArmors returns it). Not decompiled: only the methods the Player slots forward
// to are declared (all placeholder names).
class PlayerArmors {
public:
    // 0x7100e2f490 (CSV x_5): Player::m234.
    bool sub_7100E2F490();
    // 0x7100e2f000: Player::getArmorDyeStuff (a count).
    s32 sub_7100E2F000();
    // 0x7100e2f18c: Player::m280.
    bool sub_7100E2F18C();
    // 0x7100e30da8: Player::ArmorSeriesTypeStuff.
    bool sub_7100E30DA8();
    // 0x7100e313fc: Player::getMaskType (the equipment slot `idx`; the player passes 0).
    void sub_7100E313FC(s32 idx, sead::BufferedSafeString* out);

private:
    u8 _0[0x170];
};
KSYS_CHECK_SIZE_NX150(PlayerArmors, 0x170);

}  // namespace ksys::act
