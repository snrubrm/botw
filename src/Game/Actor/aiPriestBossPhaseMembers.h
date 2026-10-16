#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <container/seadSafeArray.h>
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys { class Message; }
namespace uking::ai {
class PriestBossPhaseSecond;
class PriestBossPhaseFourth;
}

// Two unnamed embedded objects of PriestBossPhaseFourth, identified by their
// SEAD RTTI vtables. Their internals are not yet recovered; these declarations
// retain the original out-of-line constructor and nonvirtual destructor calls.
class Unk_7102450fa8;

class Unk_7102451070 {
public:
    // Argument of sub_710071CB98 (placeholder)
    struct InitArg {
        Unk_7102450fa8* unit;
        f32 _8;
        f32 _c;
        f32 _10;
        bool _14;
    };

    // An entry of _38 (0x28 bytes): a member id, its actor and a position.
    struct Entry {
        s32 id = -1;
        ksys::act::BaseProcLink link;
        sead::Vector3f pos{0, 0, 0};
        f32 _24 = 0;
    };

    // 0x710071cae8 / 0x710071cb94
    Unk_7102451070();
    virtual ~Unk_7102451070();
    // 0x710071ce44 (placeholder name): with flag 0, keeps the centre _10 within sUnk_7102450fa0 of the arena centre;
    // runs the timer _20 and calls sub_710071CFF0 at 0
    void sub_710071CE44();
    // 0x710071cff0 (declared only; 1836 bytes)
    void sub_710071CFF0();
    // 0x710071cb98 (placeholder name): takes the unit and the settings and clears the entries
    void sub_710071CB98(const InitArg& arg);
    // 0x710071cc4c (placeholder name): adds an entry for member `idx` (with its actor) unless there is one
    void sub_710071CC4C(s32 idx);
    // 0x710071cdcc (placeholder name): the position of the entry `id`; false if there is none
    bool sub_710071CDCC(sead::Vector3f* out, s32 id);

    // Bits of _328 (set / reset through a stack temporary, SEAD_ENUM style).
    SEAD_ENUM(Flag, _0, _1)
    // inline-only in the original; name is a guess (sub_710071CB98 changes bit 1 through one stack temporary, the
    // same shape as Unk_7102451050::setFlag / resetFlag)
    void changeFlag(Flag flag, bool on) { _328.changeBit(flag, on); }
    // inline-only in the original; names are guesses (sub_710071CE44 tests and resets bit 0 through stack temporaries)
    bool isFlagOn(Flag flag) const { return _328.isOnBit(flag); }
    void resetFlag(Flag flag) { _328.resetBit(flag); }

private:
    friend class uking::ai::PriestBossPhaseSecond;
    friend class uking::ai::PriestBossPhaseFourth;
    /* 0x008 */ Unk_7102450fa8* _8 = nullptr;
    /* 0x010 */ sead::Vector3f _10;
    /* 0x01c */ f32 _1c = 0;
    /* 0x020 */ f32 _20 = 0;  // timer (counts down to 0, then restarts at _1c)
    /* 0x024 */ f32 _24 = 0;
    /* 0x028 */ f32 _28 = sead::Mathf::pi2();
    /* 0x02c */ f32 _2c = 0;
    /* 0x030 */ f32 _30 = 0;
    /* 0x038 */ sead::FixedObjArray<Entry, 10> _38;
    u8 _238[0x328 - 0x238];
    /* 0x328 */ sead::BitFlag32 _328;
    u8 _32c[4];
};
KSYS_CHECK_SIZE_NX150(Unk_7102451070, 0x330);

class Unk_7102451050 {
    SEAD_RTTI_BASE(Unk_7102451050)
public:
    // Argument of sub_710071BFE4 (placeholder)
    struct InitArg {
        Unk_7102450fa8* unit;
        f32 _8 = -1.0f;
        u16 _c = 1;
        bool _e = false;
    };

    // A queued request (0x20 bytes; the constructor resets the link once more).
    struct Request {
        Request() { link.reset(); }
        ~Request() { link.reset(); }

        s32 type = 0;
        ksys::act::BaseProcLink link;
        bool _18 = false;
    };

    // 0x710071bd3c / 0x710071bf08
    Unk_7102451050();
    virtual ~Unk_7102451050();
    // 0x710071bfe4 (placeholder name): takes the unit and the settings; with arg._e also starts (sub_710071C034)
    void sub_710071BFE4(const InitArg& arg);
    bool sub_710071C550(const ksys::Message& message);
    // 0x710071c034 (placeholder name): one step: counts the sleeping members (state 1 -> 2 when _1c sleep), runs
    // the timer (sub_710071C33C), handles the queued requests in state 4 and checks for the end (sub_710071C440)
    void sub_710071C034();
    // 0x710071c33c (placeholder name): in state 2, advances the timer _18; at _14 (or with flag 0) sets the unit's
    // flag 3 and goes to state 3
    void sub_710071C33C();
    // 0x710071c440 (placeholder name): in state 5, once every member entry is set and done, resets to state 1
    void sub_710071C440();
    // 0x710071c730 (placeholder name): request type 2: places the first sleeping member (2 .. 9) at the leader
    // (member 1 or 2, by the unit's phase) and records it
    void sub_710071C730(const Request& request);
    // 0x710071c89c (placeholder name): request type 3: brings the request's actor in as the first sleeping member
    // (or puts it to sleep when the member list is full)
    void sub_710071C89C(const Request& request);
    // 0x710071c1b8 (placeholder name): sets flag 0 if the unit's flag 1 is set or a member (2 .. 9) sleeps, then
    // resets the state and the member list and calls the unit's sub_71007199A8
    void sub_710071C1B8();

    // Bits of _200 (set / tested through a stack temporary, SEAD_ENUM style).
    SEAD_ENUM(Flag, _0, _1)

    // inline-only in the original; name is a guess (see PriestBossPhaseSecond::resetStateFlag)
    void resetFlag(Flag flag) { _200.resetBit(flag); }
    // inline-only in the original; name is a guess (sub_710071C33C tests the bit through a stack temporary)
    bool isFlagOn(Flag flag) const { return _200.isOnBit(flag); }
    // inline-only in the original; name is a guess (sub_710071BFE4 / sub_710071C1B8 set the bit through a stack
    // temporary, like resetFlag)
    void setFlag(Flag flag) { _200.setBit(flag); }

    /* 0x008 */ Unk_7102450fa8* _8 = nullptr;  // the meta AI unit
    /* 0x010 */ s32 _10 = 1;
    /* 0x014 */ f32 _14 = -1.0f;
    /* 0x018 */ f32 _18 = 0;  // timer
    /* 0x01c */ s16 _1c = 1;  // members that must sleep
    /* 0x01e */ s16 _1e = 0;
    /* 0x020 */ sead::FixedRingBuffer<Request, 6> _20;
    // An entry of _f8 (8 bytes).
    struct Member {
        s32 id = -1;
        bool done = false;
    };

    /* 0x0f8 */ sead::FixedObjArray<Member, 9> _f8;
    /* 0x1a8 */ Unk_7102450948 _1a8;
    /* 0x200 */ sead::BitFlag32 _200;
    u32 _204;
};
KSYS_CHECK_SIZE_NX150(Unk_7102451050, 0x208);

// PriestBossPhaseSecond's two formation controllers (its _6c0 / _958; the current one is at _6b8).
// Constructors 0x7100716a18 / 0x7100717328; base Unk_7102450fe0.

// vtable 0x7102450e00: circle formation (CircleFormRange is written to _1d8 by PriestBossPhaseSecond::enter_).
class Unk_7102450e00 : public Unk_7102450fe0 {
    SEAD_RTTI_OVERRIDE(Unk_7102450e00, Unk_7102450fe0)
public:
    // Per-member target: an angle on the circle around the player, or a fixed position.
    struct Slot {
        f32 angle;
        sead::Vector3f pos;
        bool use_angle;
    };
    KSYS_CHECK_SIZE_NX150(Slot, 0x14);

    Unk_7102450e00();
    ~Unk_7102450e00() override;
    Unk_7102450fa8::Phase m4() override { return Unk_7102450fa8::Phase::_1; }
    // 0x7100716a74
    void m7(sead::Vector3f* out, s32 idx) override;
    // 0x7100716ae0
    void m8() override;
    // 0x7100717024
    void m10() override;
    // 0x7100716f90
    virtual void m12(sead::Vector3f* out, f32 angle);

    /* 0x1d8 */ f32 _1d8 = 0;  // radius
    /* 0x1dc */ f32 _1dc = 0;  // random start angle (m10)
    /* 0x1e0 */ sead::SafeArray<Slot, 9> _1e0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450e00, 0x298);

// vtable 0x7102450ed8: line formation (LineFormSpace / LineFormDistFromPlayer go to _1d8 / _1dc).
class Unk_7102450ed8 : public Unk_7102450fe0 {
    SEAD_RTTI_OVERRIDE(Unk_7102450ed8, Unk_7102450fe0)
public:
    Unk_7102450ed8();
    ~Unk_7102450ed8() override;
    Unk_7102450fa8::Phase m4() override { return Unk_7102450fa8::Phase::_2; }
    // 0x71007173b4
    void m7(sead::Vector3f* out, s32 idx) override;
    // 0x710071741c
    void m8() override;
    // 0x7100717d88
    void m10() override;

    // 0x7100717440
    void sub_7100717440();

    /* 0x1d8 */ f32 _1d8 = 0;
    /* 0x1dc */ f32 _1dc = 0;
    /* 0x1e0 */ sead::Vector3f _1e0 = sead::Vector3f::zero;  // line origin
    /* 0x1ec */ sead::Vector3f _1ec = sead::Vector3f::zero;  // line direction
    /* 0x1f8 */ u32 _1f8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450ed8, 0x200);
