#pragma once

#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class AwarenessInstance;
}

namespace ksys::res {
class GParamListObjectWolfLink;
}

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

// vtable 0x7102432a80 (functions in this TU): accepts message type 0.
class Unk_7102432a80 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType() != 0)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

class WolfLinkNormalRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkNormalRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkNormalRoot(const InitArg& arg);
    ~WolfLinkNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // The behaviour state (_1a8: current, _1ac: pending); 16 values, names unknown (no text in the
    // executable). Passed / returned by value (a 4-byte struct travels in a 64-bit register).
    SEAD_ENUM(State, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)

    // Value of the "WarpType" parameter handed to WolfLinkWarp (the listener's payload goes through a
    // SEAD_ENUM round trip in the original); 5 values are a guess.
    SEAD_ENUM(WarpType, _0, _1, _2, _3, _4)

    // inline-only in the original; name is a guess. Whether a change to `state` is entered directly
    // instead of going through the notice children first.
    bool entersDirectly(s32 state, s32 current) const {
        if (state == current || state == 6)
            return true;
        bool enter_now = state == 4 && !_140._30;
        if (!enter_now) {
            switch (state) {
            case 1:
            case 5:
            case 8:
            case 12:
            case 13:
            case 14:
            case 15:
                enter_now = true;
                break;
            default:
                break;
            }
        }
        return enter_now;
    }

    SEAD_ENUM(Idx1bc, _0, _1, _2)
    // Bit indices of _1b8 (3 bits used) and _1b9 (6 bits used); names unknown.
    SEAD_ENUM(Flag1b8, _0, _1, _2)
    SEAD_ENUM(Flag1b9, _0, _1, _2, _3, _4, _5)

    // inline-only in the original; name is a guess. Evidence: `_1a8 == state` with a by-value State repeats
    // in four WolfLinkNormalRoot functions; the by-value State gives the enum temporaries lifetime
    // markers (shared stack slot) and the comparison goes through the enum's int conversion.
    bool isState(State state) const { return int(_1a8) == int(state); }
    // inline-only in the original; name is a guess (by-value enum parameters, as above; the flag test
    // repeats in three WolfLinkNormalRoot functions).
    f32 get1bc(Idx1bc idx) const { return _1bc[idx]; }
    bool isFlag1b8(Flag1b8 flag) const {
        const u8 mask = 1 << flag;
        return (mask & _1b8) != 0;
    }

    // Non-virtual helpers (unnamed in the original; placeholder names by address). The "state"
    // argument / _1a8 / _1ac values: 1 wait, 3 / 12 wait order, 4 follow, 5 follow retry, 6 player
    // path wait, 7 Sheikah sensor, 8 howl, 9 hunt, 10 battle, 11 heal, 13-15 warp.
    // 0x606bb4 (CSV wolfLinkNormalRootCalc): enters `state`; false if it cannot be entered.
    bool sub_7100606BB4(State state, bool force);
    bool sub_7100606FCC();
    // 0x607140: picks the next state.
    State sub_7100607140();
    void sub_7100607910();
    void sub_7100607A2C();
    void sub_7100607D00();
    void sub_7100608200();
    void sub_71006082FC(bool changeable);
    bool sub_71006085C8(State state);
    bool sub_71006088AC();
    // 0x608b6c (CSV wolfLinkNormalRootCalcGoToBattle)
    bool sub_7100608B6C(bool force);
    bool sub_7100608C84();
    bool sub_7100608DFC();
    bool sub_7100608F0C();
    bool sub_71006090A0();
    bool sub_7100609190();
    bool sub_7100609288();
    bool sub_7100609378(State state);
    bool sub_71006094FC();
    bool sub_7100609628();
    bool sub_7100609738();
    bool sub_710060980C();
    f32 getUtilityDangerMaybe();
    bool sub_7100609AC0();
    void sub_7100609DFC();

    // static_param at offset 0x38
    const float* mShiekSensorLeadDistance_s{};
    // static_param at offset 0x40
    const float* mShiekSensorGoalTolerance_s{};
    // static_param at offset 0x48
    const float* mShiekSensorTargetFowardOffset_s{};
    // static_param at offset 0x50
    const float* mBattleAggressionRange_s{};
    // static_param at offset 0x58
    const float* mHowlAtEnemyRange_s{};
    // static_param at offset 0x60
    const float* mUtilityWantsToHunt_s{};
    // static_param at offset 0x68
    const float* mWarpToPlayerDistance_s{};
    act::WolfLink* _70{};
    const ksys::res::GParamListObjectWolfLink* _78{};
    ksys::act::AwarenessInstance* _80{};
    Unk_7102450648 _88{0x1800025};
    Unk_7102450648 _c8{0x1800024};
    Unk_7102450bb8 _108;
    Unk_7102432a80 _140;
    sead::Vector3f _178 = {0, 0, 0};
    sead::Vector3f _184 = {0, 0, 0};
    sead::Vector3f _190 = {0, 0, 0};
    sead::Vector3f _19c = {0, 0, 0};
    State _1a8{State::_0};
    State _1ac{State::_4};
    u32 _1b0 = 0;
    u32 _1b4 = 0;
    u8 _1b8 = 0;
    u8 _1b9 = 0;
    // [0]: life-based factor (calc_), [2]: threshold; indexed with a SEAD_ENUM (3 values) in the original
    sead::SafeArray<f32, 3> _1bc{};
    f32 _1c8 = 0;
};
KSYS_CHECK_SIZE_NX150(WolfLinkNormalRoot, 0x1d0);

}  // namespace uking::ai
