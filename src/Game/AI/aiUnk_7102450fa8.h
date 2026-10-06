#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
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
class Unk_7102450fa8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450fa8, Unk_71025afb58)
public:
    SEAD_ENUM(Phase, _0, _1, _2, _3, _4)
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)

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
    void sub_7100719D5C(ksys::act::Actor* actor);
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
    // `_3c8 > 0 && _350 has ended`. Placeholder name.
    bool sub_710071A22C();
    // `_35c has ended`. Placeholder name.
    bool sub_710071A2D0();

    /* 0x008 */ sead::Buffer<Unk1> _8;
    /* 0x018 */ ksys::act::BaseProcLink _18;
    /* 0x028 */ ksys::act::BaseProcLink _28;
    /* 0x038 */ Phase _38;
    /* 0x03c */ Phase _3c;
    /* 0x040 */ f32 _40;  // compared with PriestBossActorNormalMode's SecondHalfLifePercent
    /* 0x044 */ u8 _44[0x78 - 0x44];
    /* 0x078 */ sead::BitFlag32 _78;
    /* 0x07c */ u8 _7c[0x80 - 0x7c];
    /* 0x080 */ u32 _80;  // bit mask indexed by Phase-like ints 3..10 (sub_7100719978)
    /* 0x084 */ u8 _84[0xa0 - 0x84];
    /* 0x0a0 */ u8 _a0[0x1a0 - 0xa0];  // sead::FixedObjArray<?, 9> (0x10-byte nodes) at 0xa0
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
    /* 0x348 */ s32 _348;  // PriestBossPhaseThird::enter_: BreakIronBallCount
    /* 0x34c */ sead::Atomic<u32> _34c;
    /* 0x350 */ ksys::Timer _350;
    /* 0x35c */ ksys::Timer _35c;  // PriestBossIronBall::sub_710051EE40: ChangeEndAnime
    /* 0x368 */ Unk_71024508b8 _368;
    /* 0x3c8 */ f32 _3c8;
    /* 0x3cc */ bool _3cc;  // PriestBossIronBallRoot::enter_
    /* 0x3cd */ u8 _3cd[0x43c - 0x3cd];  // BaseProcLink at 0x3d0; sead::FixedRingBuffer<?, 6> at 0x3f0
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
