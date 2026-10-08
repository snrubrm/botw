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
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class Message;
}

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class BaseProc;
}  // namespace ksys::act

// Unnamed class of the object shared by the PriestBoss* AI trees through the
// "PriestBossMetaAIUnit" AI tree variable. Created by PriestBossMetaAIRoot::init_ (create 0x7100718360,
// ctor 0x7100717eec, init 0x71007183a4); its functions live at 0x7100717000-0x710071c000.
// Placeholder name = vtable address. Only the members used by its users are declared.
// Placeholder (lane4 s50; vtable unknown): the object at Unk_7102450fa8::_88. Only what the wrappers use is declared:
// virtual slots 6 / 7 and the fields `_ac` / `_b8` (an array of pointers to s16 values, indexed by phase - 2).
struct Unk_PriestBossObject {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
    virtual void m5();
    virtual s32 m6(s32 idx);
    virtual void m7(sead::Vector3f* out, s32 idx);

    u8 _8[0xa8 - 0x8];
    /* 0xa8 */ s32 _a8;
    /* 0xac */ s32 _ac;
    u8 _b0[0xb8 - 0xb0];
    /* 0xb8 */ s16** _b8;
};

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
    // 0x7100719b88 (468 B, declared only; PriestBossActorNormalMode::m40)
    bool sub_7100719B88(ksys::act::Actor* actor);
    // Sends message 0x80000d9 (payload = this) from the actor of _18 to `dest`.
    void sub_71007190CC(const ksys::MesTransceiverId& dest);
    void sub_710071964C(const Unk3& arg);

    bool sub_71007194CC(ksys::act::ActorConstDataAccess* accessor);
    bool sub_71007194D4(int idx, ksys::act::ActorConstDataAccess* accessor);
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
    bool sub_710071A38C(const ksys::act::ActorConstDataAccess* accessor);

    /* 0x008 */ sead::Buffer<Unk1> _8;
    /* 0x018 */ ksys::act::BaseProcLink _18;
    /* 0x028 */ ksys::act::BaseProcLink _28;
    /* 0x038 */ Phase _38;
    /* 0x03c */ Phase _3c;
    /* 0x040 */ f32 _40;  // compared with PriestBossActorNormalMode's SecondHalfLifePercent
    /* 0x044 */ u8 _44[0x50 - 0x44];
    // Cleared together with `_80` by sub_71007199A8.
    /* 0x050 */ u64 _50;
    /* 0x058 */ u64 _58;
    /* 0x060 */ u64 _60;
    /* 0x068 */ u64 _68;
    /* 0x070 */ u64 _70;
    /* 0x078 */ sead::BitFlag32 _78;
    /* 0x07c */ u8 _7c[0x80 - 0x7c];
    /* 0x080 */ u32 _80;  // bit mask indexed by Phase-like ints 3..10 (sub_7100719978)
    /* 0x084 */ u8 _84[0x88 - 0x84];
    /* 0x088 */ Unk_PriestBossObject* _88;
    /* 0x090 */ u8 _90[0x98 - 0x90];
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
    /* 0x438 */ u8 _438[0x43c - 0x438];
    /* 0x43c */ f32 _43c;  // PriestBossIronBallRoot::m38: attack power (int-converted)
    /* 0x440 */ f32 _440;  // PriestBossIronBallRoot::m38(true): attack power
    /* 0x444 */ bool _444;  // PriestBossActorGiantFouthRoot::m46 (cleared when read)
    /* 0x445 */ u8 _445[0x448 - 0x445];
};
KSYS_CHECK_SIZE_NX150(Unk_7102450fa8, 0x448);

// Global Vector3f in the unit's TU (0x71025c8cf8), set to {0, 0, 900} by the TU's static initialiser
// (0x710071a8f4); copied to PriestBossGiantStageRotRoot's FacePos. Placeholder name.
extern sead::Vector3f sUnk_71025c8cf8;
// Global constant in the unit's TU (0x7102450fa0, right before its vtable): 50.0 (the default arena
// radius, see Unk3::_c). Placeholder name.
extern const f32 sUnk_7102450fa0;
// Global in the unit's TU (0x7102450f80): the three arrow actors the Priest Boss fires (fire / ice /
// electric); PriestBossPhase::m40 stores a random one into `_2b0`. Placeholder name.
extern const sead::SafeArray<const char*, 3> sUnk_7102450f80;
// The part actor name of the grave (0x7102450f98, the pointer right after the three arrow names). Placeholder name.
extern const char* const sUnk_7102450f98;
