#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
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
    // 0x7100e2edf8 (CSV x_3): Player::getArmorPartName (the name of the actor in part slot `idx`).
    void sub_7100E2EDF8(s32 idx, sead::BufferedSafeString* out);
    // 0x7100e2ed78 (CSV x_4): Player::m278 (-1 when slot `idx` > 2 or empty).
    s32 sub_7100E2ED78(s32 idx);
    // 0x7100e30c78 (unnamed): Player::armorSeriesStuff (series type of part `idx` == `series`).
    bool sub_7100E30C78(s32 idx, const sead::SafeString& series);
    // 0x7100e2f61c (CSV x_0; out of line, returns `&_134`): the armor effect flags (bit 0: swim energy,
    // bit 7: bone attack, bit 8: climb jump energy, bit 9: drop rate bonus are active).
    sead::BitFlag16* sub_7100E2F61C();
    // 0x7100e303e4 (declared only).
    bool hasAncientPowUpEffect();
    // 0x7100e2f490 (CSV x_5): Player::m234.
    s32 sub_7100E2F490();
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

    // 0x7100e31574 (lane4 s31): puts every worn part to sleep (ActorConstDataAccess::sleep for each linked actor).
    void sleep(BaseProc::SleepWakeReason reason);
    // 0x7100e3170c (declared only): wakes up the first 3 / 6 parts depending on a gdt flag.
    void sub_7100E3170C(BaseProc::SleepWakeReason reason);
    // 0x7100e2f428 (CSV x_22): the upper armor (`_10[1]`) disables its own mantle (acc::Armor::getArmorUpperDisableSelfMantle;
    // false without an upper armor).
    bool sub_7100E2F428();
    // 0x7100e2f358 (CSV x_24): the head armor (`_10[0]`) has a mantle (acc::Armor::sub_7100E2BF44; false without a head armor).
    bool sub_7100E2F358();

    // Inline in the original (uking::act::Armor::m148).
    bool get133() const { return _133; }

    // Inline-only in the original (Player::m276 / m277); name is a guess.
    BaseProcLink& getPartsLink(int idx) { return _10[idx]; }

private:
    u8 _0[0x10];
    sead::SafeArray<BaseProcLink, 6> _10;
    u8 _70[0x133 - 0x70];
    u8 _133;  // read by uking::act::Armor::m148 (the head armor then uses weight 0)
    sead::BitFlag16 _134;
    u8 _136[0x170 - 0x136];
};
KSYS_CHECK_SIZE_NX150(PlayerArmors, 0x170);

}  // namespace ksys::act
