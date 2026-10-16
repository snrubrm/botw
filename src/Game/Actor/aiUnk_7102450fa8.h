#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadRingBuffer.h>
#include <mc/seadJobQueue.h>
#include <prim/seadScopedLock.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <thread/seadAtomic.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_71025afb58.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

class Unk_7102451070;

namespace ksys {
class Message;
}

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
class ActorLinkConstDataAccess;
class BaseProc;
}  // namespace ksys::act

class Unk_7102450fa8;

class Unk_7102450fe0;

// Unnamed class of the object shared by the PriestBoss* AI trees through the
// "PriestBossMetaAIUnit" AI tree variable. Created by PriestBossMetaAIRoot::init_ (create 0x7100718360,
// ctor 0x7100717eec, init 0x71007183a4); its functions live at 0x7100717000-0x710071c000.
// Placeholder name = vtable address. Only the members used by its users are declared.

class Unk_7102450fa8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450fa8, Unk_71025afb58)
public:
    SEAD_ENUM(Phase, _0, _1, _2, _3, _4)
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)

    // Element of the 33-entry buffer allocated by the init function (0x71007183a4).
    struct Unk1 {
        u32 _0 = 0;
        ksys::act::InstParamPack _8;
        ksys::act::BaseProcLink _e0;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0xf0);

    // Argument of the init function (built by PriestBossMetaAIRoot::init_).
    struct Unk2 {
        sead::Vector3f _0;  // the owner actor's position
        ksys::act::Actor* _10;
        const sead::SafeString* _18;  // BowActorName
        const sead::SafeString* _20;  // WeaponActorName
        const sead::SafeString* _28;  // ThunderActorName
    };
    KSYS_CHECK_SIZE_NX150(Unk2, 0x30);

    // Filled by PriestBossMetaAIRoot (0x710052656c) from the actor of its map object's first link.
    struct Unk3 {
        sead::Vector3f _0;  // the linked actor's position
        f32 _c;             // radius of its GeneralSensor/BattleArea body (default 50)
        ksys::MesTransceiverId _10;
    };
    KSYS_CHECK_SIZE_NX150(Unk3, 0x28);

    ~Unk_7102450fa8() override;
    // vtable slot 4: handles the messages for the embedded listeners (0x710071a410).
    virtual bool m4(const ksys::Message& message);

    // 0x7100718360: allocates and constructs the object (ctor 0x7100717eec).
    static Unk_7102450fa8* sub_7100718360(sead::Heap* heap);
    bool sub_71007183A4(sead::Heap* heap, const Unk2& arg);
    // inline-only in the original; name is a guess. Evidence: PriestBossMetaAIRoot::calc_ tests the flag
    // through a by-value enum parameter (the enum temporary shares the stack slot of `arg`: lifetime
    // markers); only that one call site is known, the same shape appears in the other PriestBoss*
    // flag tests (IronBallRoot::m41, BananaMode).
    bool isFlagOn(Flag flag) const { return _78.isOnBit(flag); }
    // inline-only in the original; names are guesses. Same evidence as isFlagOn: in PriestBossPhaseSecond leave_,
    // sub_710052B4D0 and handleMessage_ every flag index temporary shares one stack slot with the other locals.
    void setFlag(Flag flag) { _78.setBit(flag); }
    void resetFlag(Flag flag) { _78.resetBit(flag); }
    // inline-only in the original; name is a guess (PriestBossPhaseSecond::calc_ inlines it twice)
    void clearFlags8And9Maybe() {
        resetFlag(Flag::_8);
        if (isFlagOn(Flag::_9))
            resetFlag(Flag::_9);
    }
    // 0x7100719fe4: `_88 ? _88->vslot6(idx) : 3` (unnamed object at 0x88).
    s32 sub_7100719FE4(s32 idx);
    // 0x7100719978: `idx != 2 && idx - 2 <= 8 && (_80 >> idx & 1)`. Placeholder name.
    bool sub_7100719978(s32 idx) const;
    // 0x7100719fcc (CSV name was a bogus nn::nex symbol): `_88 ? _88->_ac : -1`.
    s32 sub_7100719FCC() const;
    void sub_710071918C();
    // Original 0x7100719ed0: clears the linked actor pool under its lock (declared only).
    void sub_7100719ED0();
    void sub_7100719D5C(ksys::act::Actor* actor);
    // 0x7100719b78 (declared only): `_90 ? _90->sub_710071CDCC(out, idx) : false` (_90 unmodelled; its
    // function looks `idx` up in a pointer array and copies the entry's position at +0x18).
    bool sub_7100719B78(sead::Vector3f* out, s32 idx);
    // 0x7100719b88 (468 B, declared only; PriestBossActorNormalMode::m40)
    bool sub_7100719B88(ksys::act::Actor* actor);
    // Sends message 0x80000d9 (payload = this) from the actor of _18 to `dest`.
    void sub_71007190CC(const ksys::MesTransceiverId& dest);
    void sub_710071964C(const Unk3& arg);

    bool sub_71007194CC(ksys::act::ActorLinkConstDataAccess* accessor);
    bool sub_71007194D4(int idx, ksys::act::ActorLinkConstDataAccess* accessor);
    int sub_7100719534(ksys::act::BaseProc* proc);
    int sub_71007195B0(const ksys::act::BaseProcLink& link);
    // 0x710071a020: if the object at +0x88 exists, calls its vtable slot 7 with (out, idx) and returns
    // true (the formation position of `idx`). Placeholder name.
    bool sub_710071A020(sead::Vector3f* out, s32 idx);
    s32 sub_710071A048(s32 idx);
    // 0x7100719fa4: `_88 ? _88->_a8 : 0`. Placeholder name.
    s32 sub_7100719FA4();
    // `_3c8 > 0 && _350 has ended`. Placeholder name.
    bool sub_710071A22C();
    // `_35c has ended`. Placeholder name.
    bool sub_710071A2D0();
    // 0x710071962c: copies the global {0, 0, 900} (sUnk_71025c8cf8) to `out` and returns true. Placeholder name.
    bool sub_710071962C(sead::Vector3f* out);
    // 0x71007196ec: places the sleeping member `idx` at `pos` and gives it the next side offset
    bool sub_71007196EC(s32 idx, const sead::Vector3f& pos);
    // 0x71007199a8: zeroes `_50`..`_70` and `_80`. Placeholder name.
    void sub_71007199A8();
    // 0x7100719f70: `_88 ? _88->m4() : 0` (result goes through a Phase temporary). Placeholder name.
    s32 sub_7100719F70();
    // 0x710071a1c0: pushes (a, b) into the ring buffer `_3f0`. Placeholder name.
    void sub_710071A1C0(u32 a, u32 b);
    // 0x710071a200: `_348 > 0 && _34c >= _348` (signed). Placeholder name.
    bool sub_710071A200() const;
    // 0x710071a258 / 0x710071a2e8: update the timers `_350` / `_3e0` (resp. `_35c`) unless the actor of
    // `_8[1]` is found and its sub_7100D10FB8 is set. Placeholder names.
    void sub_710071A258();
    void sub_710071A2E8();
    // 0x710071a38c: true if `_3e0` has not run out and the actor of `_3d0` is the one held by `accessor`.
    // Placeholder name.
    bool sub_710071A38C(const ksys::act::ActorLinkConstDataAccess* accessor);

    /* 0x008 */ sead::Buffer<Unk1> _8;
    /* 0x018 */ ksys::act::BaseProcLink _18;
    /* 0x028 */ ksys::act::BaseProcLink _28;
    /* 0x038 */ Phase _38;
    /* 0x03c */ Phase _3c;
    /* 0x040 */ f32 _40;  // compared with PriestBossActorNormalMode's SecondHalfLifePercent
    /* 0x044 */ f32 _44;  // RespawnBaseSpace (PriestBossPhaseSecond::enter_)
    /* 0x048 */ f32 _48;  // RespawnBaseMoveTime
    /* 0x04c */ f32 _4c;  // RespawnBaseInterval
    // Cleared together with `_80` by sub_71007199A8.
    /* 0x050 */ sead::SafeArray<s32, 8> _50;  // per member 3 .. 10: alternating side offset (sub_71007196EC)
    /* 0x070 */ s32 _70;
    /* 0x074 */ s32 _74;  // number of members placed (sub_71007196EC)
    /* 0x078 */ sead::BitFlag32 _78;
    /* 0x07c */ u8 _7c[0x80 - 0x7c];
    /* 0x080 */ u32 _80;  // bit mask indexed by Phase-like ints 3..10 (sub_7100719978)
    /* 0x084 */ u8 _84[0x88 - 0x84];
    /* 0x088 */ Unk_7102450fe0* _88;
    /* 0x090 */ Unk_7102451070* _90;  // set by PriestBossPhaseFourth::enter_ (its _98)
    /* 0x098 */ u32 _98;
    /* 0x09c */ sead::JobQueueLock _9c;
    /* 0x0a0 */ sead::FixedObjArray<ksys::act::BaseProcLink, 9> _a0;
    /* 0x198 */ u32 _198;
    /* 0x19c */ u8 _19c[4];
    /* 0x1a0 */ ksys::MesTransceiverId _1a0;  // set from Unk3::_10 by sub_710071964C
    /* 0x1b8 */ Unk_71024509a8 _1b8;
    /* 0x200 */ u8 _200[0x208 - 0x200];
    /* 0x208 */ Unk_7102450858 _208;
    // Per-phase flags (PriestBossActorEnemyRoot::m52 reads `_248[_3c]._0`); 3 bytes per phase.
    struct PhaseFlags {
        bool _0;
        bool _1;
        bool _2;
    };
    /* 0x248 */ sead::SafeArray<PhaseFlags, 5> _248;
    // inline-only in the original; name is a guess (PriestBossPhaseSecond::calc_: the phase index temporary
    // shares the stack slot of a later local, as an inlined by-value parameter does)
    const PhaseFlags& getPhaseFlags(Phase phase) const { return _248[phase]; }
    /* 0x257 */ u8 _257;
    /* 0x258 */ Unk_7102450918 _258;
    /* 0x2b0 */ sead::FixedSafeString<128> _2b0;
    /* 0x348 */ sead::Atomic<s32> _348;  // PriestBossPhaseThird::enter_: BreakIronBallCount; read twice (volatile) by sub_710071A200
    /* 0x34c */ sead::Atomic<s32> _34c;  // compared as signed with `_348` by sub_710071A200
    /* 0x350 */ ksys::Timer _350;
    /* 0x35c */ ksys::Timer _35c;  // PriestBossIronBall::sub_710051EE40: ChangeEndAnime
    /* 0x368 */ Unk_71024508b8 _368;
    /* 0x3c8 */ f32 _3c8;
    /* 0x3cc */ bool _3cc;  // PriestBossIronBallRoot::enter_
    /* 0x3cd */ u8 _3cd[0x3d0 - 0x3cd];
    /* 0x3d0 */ ksys::act::BaseProcLink _3d0;  // used by sub_710071A38C (hasProc / acquireActor)
    /* 0x3e0 */ ksys::Timer _3e0;
    // Elements pushed by sub_710071A1C0 (two 32-bit values).
    struct Unk4 {
        u32 _0;
        u32 _4;
    };
    /* 0x3f0 */ sead::FixedRingBuffer<Unk4, 6> _3f0;
    /* 0x438 */ f32 _438;  // iron ball speed threshold (PriestBossIronBallRoot::sub_7100521870)
    /* 0x43c */ f32 _43c;  // PriestBossIronBallRoot::m38: attack power (int-converted)
    /* 0x440 */ f32 _440;  // PriestBossIronBallRoot::m38(true): attack power
    /* 0x444 */ bool _444;  // PriestBossActorGiantFouthRoot::m46 (cleared when read)
    /* 0x445 */ u8 _445[0x448 - 0x445];
};
KSYS_CHECK_SIZE_NX150(Unk_7102450fa8, 0x448);

// vtable 0x7102450fe0: base class of the two PriestBossPhaseSecond formation controllers (Unk_7102450e00,
// Unk_7102450ed8) and the object at Unk_7102450fa8::_88. Layout from the constructor 0x710071a92c and
// the destructor 0x710071ab84. Own TU 0x710071a92c .. 0x710071bd38 (aiUnk_7102450fe0.cpp).
class Unk_7102450fe0 {
    SEAD_RTTI_BASE(Unk_7102450fe0)
public:
    SEAD_ENUM(Flag, _0, _1, _2)
    // Index into the m11 table (passed by value through the stack, as a SEAD_ENUM).
    SEAD_ENUM(Step, _0, _1, _2, _3, _4, _5, _6, _7, _8)

    // One per formation member (index = member id - 2). Reset field by field in 0x710071ac54 / 0x710071aecc.
    struct Entry {
        void reset(s32 state) {
            _0 = state;
            _4 = 0;
            _8 = 0;
            _c = false;
        }

        s32 _0 = 0;  // state (index into the m11 table)
        s32 _4 = 0;  // last state value reported by the member's message (m9)
        f32 _8;      // time in the state (sub_710071B6A4)
        bool _c;     // state done
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x10);

    // Element of the static table returned by m11 (0x710071b4d0; 9 entries of 0x18 bytes).
    struct State {
        // The table is built by a guarded dynamic initialiser, so this is not an aggregate.
        State(void (*func_)(Unk_7102450fe0*, s32), s32 a, s32 b, bool c, bool d)
            : func(func_), _8(a), _c(b), _10(c), _11(d) {}

        void (*func)(Unk_7102450fe0* self, s32 idx);
        s32 _8;
        s32 _c;
        bool _10;
        bool _11;
    };
    KSYS_CHECK_SIZE_NX150(State, 0x18);

    Unk_7102450fe0();
    virtual ~Unk_7102450fe0();
    virtual Unk_7102450fa8::Phase m4() { return Unk_7102450fa8::Phase::_0; }
    // 0x710071ac54
    virtual void m5(s32 a8, f32 x, f32 y);
    // 0x71007171b0 (emitted in the Unk_7102450e00 TU)
    virtual s32 m6(s32 idx) { return _8[idx - 2]._0; }
    virtual void m7(sead::Vector3f* out, s32 idx) {}
    // 0x710071aea0
    virtual void m8();
    // 0x710071b2ac
    virtual bool m9(const ksys::Message& message);
    // 0x710071b3a4
    virtual void m10();
    // 0x710071b4d0
    virtual const State* m11(Step step);

    bool isFlagOn(Flag flag) const { return _1d0.isOnBit(flag); }
    // inline-only in the original; name is a guess (m5: the flag index temporary shares the accessor's stack slot)
    void setFlag(Flag flag) { _1d0.setBit(flag); }

    // 0x710071b5ec / 0x710071b6a4: m11 table callbacks (per member update).
    static void sub_710071B5EC(Unk_7102450fe0* self, s32 idx);
    static void sub_710071B6A4(Unk_7102450fe0* self, s32 idx);

    // 0x710071b37c
    void sub_710071B37C(Unk_7102450fa8* unit);
    // 0x710071aecc
    void sub_710071AECC();
    // 0x710071b7d4: whether every member is in `state` and done
    bool sub_710071B7D4(Step state) const;
    // 0x710071b8c4: whether every member's step has the _11 flag (final step)
    bool sub_710071B8C4();
    // 0x710071ba04: whether any member is in `state`
    bool sub_710071BA04(Step state) const;

    // inline-only in the original; name is a guess (m5, sub_710071AECC (twice): the same nine unrolled resets, with the
    // step loaded once)
    void resetEntries(s32 state) {
        for (auto& entry : _8)
            entry.reset(state);
    }

    // inline-only in the original; name is a guess (the constructor 0x710071a92c and m10 0x710071b3a4 repeat it)
    void resetOrder() {
        _b0.clear();
        for (s32 i = 0; i < 9; ++i)
            _b0.emplaceBack(i);
    }

    /* 0x008 */ sead::SafeArray<Entry, 9> _8;
    /* 0x098 */ f32 _98 = 0.1f;
    /* 0x0a0 */ Unk_7102450fa8* _a0 = nullptr;
    /* 0x0a8 */ s32 _a8 = 0;
    /* 0x0ac */ s32 _ac = 0;  // counter, wraps at 10000 (m5)
    /* 0x0b0 */ sead::FixedObjArray<s16, 9> _b0;  // member order (shuffled by m10)
    /* 0x160 */ sead::Vector3f _160 = sead::Vector3f::zero;
    /* 0x16c */ f32 _16c = 0;
    /* 0x170 */ f32 _170 = 0;
    /* 0x178 */ Unk_7102450888 _178;
    /* 0x1d0 */ sead::BitFlag32 _1d0;
    /* 0x1d4 */ u32 _1d4 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450fe0, 0x1d8);

// Global Vector3f in the unit's TU (0x71025c8cf8), set to {0, 0, 900} by the TU's static initialiser
// (0x710071a7b4); copied to PriestBossGiantStageRotRoot's FacePos. Placeholder name.
extern sead::Vector3f sUnk_71025c8cf8;
// Global Vector3f right after sUnk_71025c8cf8 (0x71025c8d04); PriestBossActorNormalRoot::m35 spawns the boss's
// weapons there. Placeholder name.
extern sead::Vector3f sUnk_71025c8d04;
// Global in the unit's TU (0x7102450fa0, right before its vtable): 50.0 (the default arena
// radius, see Unk3::_c). Placeholder name.
extern f32 sUnk_7102450fa0;
// Global in the unit's TU (0x7102450f80): the three arrow actors the Priest Boss fires (fire / ice /
// electric); PriestBossPhase::m40 stores a random one into `_2b0`. Placeholder name.
extern const sead::SafeArray<const char*, 3> sUnk_7102450f80;
// The part actor name of the grave (0x7102450f98, the pointer right after the three arrow names). Placeholder name.
extern const char* const sUnk_7102450f98;
