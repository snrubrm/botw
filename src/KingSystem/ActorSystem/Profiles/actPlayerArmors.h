#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
struct Unk117;

// Placeholder name (CSV: PlayerArmors::x_3 / x_4 / x_5 and unnamed methods in the TU
// 0x7100e2c1fc-0x7100e31570): the player's armor state, embedded in Player at +0x23e0 (0x170
// bytes; Actor::getArmors returns it). Not decompiled: only the methods the Player slots forward
// to are declared (all placeholder names).
// Placeholder name: the second base of PlayerArmors (vptr at +8; the vtable at 0x71024e5ed0 + 0x38 only
// holds its two destructors, there is no data).
class PlayerArmorsUnkBase8 {
public:
    virtual ~PlayerArmorsUnkBase8() = default;
};

// The first base (vptr at +0) is IHandler: the vtable at 0x71024e5ed0 + 0x10 is {D1 0x7100e2d66c, D0 0x7100e2d7b0,
// handleAck = the shared empty function 0x710064c188}.
class PlayerArmors : public MessageTransceiverTxOnly::IHandler, public PlayerArmorsUnkBase8 {
public:
    // 0x7100e2d490 (CSV PlayerArmors::ctor); `flag` is stored in `_130` (Player passes it).
    explicit PlayerArmors(bool flag);
    // 0x7100e2d66c (D1) / 0x7100e2d7b0 (D0) + the 0x7100e2d7a8 / 0x7100e2d7d4 thunks of the second base.
    ~PlayerArmors() override;

    // 0x7100e317f0 (CSV x_36; name is a guess): sends the message 0x4000001 (AnmArmorBindAction handles it) to the
    // first three worn parts through `mTransceiver`.
    void sub_7100E317F0();

    // 0x7100e2d70c (called by the destructor; CSV unnamed): deletes the six worn part actors (the part
    // handles and the linked actors).
    void sub_7100E2D70C();

    // 0x7100e2edf8 (CSV x_3): Player::getArmorPartName (the name of the actor in part slot `idx`).
    void sub_7100E2EDF8(s32 idx, sead::BufferedSafeString* out);
    // 0x7100e2ed78 (CSV x_4): Player::m278 (-1 when slot `idx` > 2 or empty).
    s32 sub_7100E2ED78(s32 idx);
    // 0x7100e30b00 (CSV x_35): the series type of part `idx` (empty without a part). 0x7100e313fc (unnamed): the head mask
    // type of part `idx` (empty without a part).
    void sub_7100E30B00(s32 idx, sead::BufferedSafeString* out);
    // 0x7100e30c78 (unnamed): Player::armorSeriesStuff (series type of part `idx` == `series`).
    bool sub_7100E30C78(s32 idx, const sead::SafeString& series);
    // 0x7100e2f61c (CSV x_0; out of line, returns `&_134`): the armor effect flags (bit 0: swim energy,
    // bit 7: bone attack, bit 8: climb jump energy, bit 9: drop rate bonus are active).
    // Placeholder (lane4 s46): the armor effect flags (`_134`): 16 flag bits, then flag bytes (bit 2 of `_2`: read by
    // Player::sub_710086D138; bit 3 of `_2`: sub_7100E308E4).
    struct EffectFlags {
        bool isOnBit(int bit) const { return flags.isOnBit(bit); }

        sead::BitFlag16 flags;
        u8 _2 = 0;
        u8 _3 = 0;
    };
    EffectFlags* sub_7100E2F61C();
    // 0x7100e303e4.
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

    // Effect level sums (lane4 s44; the names are guesses: effect strings from the table 0x7102602358).
    // 0xe2f624 (CSV x_21): the summed level of the effect "ResistBurn" of the first three parts.
    s32 getArmorEffectLevelResistBurn();
    // 0xe2f734 (CSV x_1): the summed level of the effect "ResistCold" of the first three parts.
    s32 getArmorEffectLevelResistCold();
    // 0xe2f844 (CSV x_11): the summed level of the effect "ResistFreeze" of the first three parts.
    s32 getArmorEffectLevelResistFreeze();
    // 0xe2fa78 (CSV x_13): the summed level of the effect "ResistLightning" of the first three parts.
    s32 getArmorEffectLevelResistLightning();
    // 0xe2fb88 (CSV x_14): the summed level of the effect "SwimSpeed" of the first three parts.
    s32 getArmorEffectLevelSwimSpeed();
    // 0xe2fc98 (CSV x_15): the summed level of the effect "ClimbSpeed" of the first three parts.
    s32 getArmorEffectLevelClimbSpeed();
    // 0xe2fda8 (CSV x_16): the summed level of the effect "AttackUp" of the first three parts.
    s32 getArmorEffectLevelAttackUp();
    // 0xe2ffa4 (CSV x_18): the summed level of the effect "Quietness" of the first three parts.
    s32 getArmorEffectLevelQuietness();
    // 0xe300b4 (CSV x_19): the summed level of the effect "SandMove" of the first three parts.
    s32 getArmorEffectLevelSandMove();
    // 0xe301c4 (CSV x_20): the summed level of the effect "SnowMove" of the first three parts.
    s32 getArmorEffectLevelSnowMove();
    // 0xe302d4 (CSV x_10): the summed level of the effect "ResistAncient" of the first three parts.
    s32 getArmorEffectLevelResistAncient();
    // 0xe306b4 (CSV x_6): the summed level of the effect "ClimbSpeedHorizontalOnly" of the first three parts.
    s32 getArmorEffectLevelClimbSpeedHorizontalOnly();

    // 0x7100e2feb8 (CSV x_17): the summed defence add level of the first three parts.
    s32 getArmorDefenceAddLevelSum();
    // 0x7100e304d4 (CSV x_8) / 0x7100e305c4 (CSV x_7) / 0x7100e30a0c (CSV x_34): one of the first three parts enables
    // climbing waterfalls / the spin attack / has the series completion bonus.
    bool hasEnableClimbWaterfall();
    bool hasEnableSpinAttack();
    bool hasSeriesCompBonus();

    // 0x7100e2f4f8 (CSV x): summed "ResistHot" level (1 when it is 0 and `_134` bit 2 is set).
    s32 getArmorEffectLevelResistHot();
    // 0x7100e2f954 (CSV x_12): 3 when "ResistLightning" is active, else the summed "ResistElectric" level.
    s32 getArmorEffectLevelResistElectric();
    // 0x7100e307c4: "WakeWind" is active.
    bool hasWakeWindArmorEffect();
    // 0x7100e308e4 (CSV x_33): `_136` bit 3 is set or "BeamPowerUp" is active.
    bool hasBeamPowerUpEffect();

    // 0x7100e2f3c0 (CSV x_23): the head armor's mantle type (0 without a head armor).
    s32 getHeadMantleType();
    // 0x7100e2ed08 (CSV x_25): none of the six parts is being created (and none has failed).
    bool hasNoPartBeingCreated();
    // 0x7100e2d804 (CSV x_26): wakes up the parts 3-5; 0x7100e2d890 (CSV x_27): puts part 5 to sleep.
    void wakeUpExtraParts();
    void sleepLastPart();

    // 0x7100e2d7fc (CSV setActor).
    void setActor(Actor* actor);

    // Inline in the original (uking::act::Armor::m148).
    bool get133() const { return _133; }

    // Inline-only in the original (Player::m276 / m277); name is a guess.
    BaseProcLink& getPartsLink(int idx) { return _10[idx]; }

private:
    sead::SafeArray<BaseProcLink, 6> _10;
    sead::SafeArray<BaseProcHandle, 6> _70;
    u8 _d0 = 0;
    /* 0xd8 */ MessageTransceiverTxOnly mTransceiver{this};
    Actor* _128 = nullptr;  // the owner (setActor)
    bool _130;
    u8 _131 = 0;
    u8 _132 = 0;
    u8 _133 = 0;  // read by uking::act::Armor::m148 (the head armor then uses weight 0)
    EffectFlags _134;
    sead::FixedSafeString<32> _138{sead::SafeString::cEmptyString};
};
KSYS_CHECK_SIZE_NX150(PlayerArmors, 0x170);

}  // namespace ksys::act
