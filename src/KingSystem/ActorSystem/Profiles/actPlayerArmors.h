#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

struct Unk117;

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
    // 0x7100e31b9c (CSV x_38): Player::m117 (declared only).
    void sub_7100E31B9C(Unk117* arg);

    // Inline-only in the original (Player::m276 / m277); name is a guess.
    BaseProcLink& getPartsLink(int idx) { return _10[idx]; }

private:
    u8 _0[0x10];
    sead::SafeArray<BaseProcLink, 6> _10;
    u8 _70[0x170 - 0x70];
};
KSYS_CHECK_SIZE_NX150(PlayerArmors, 0x170);

}  // namespace ksys::act
