#pragma once

#include <basis/seadTypes.h>
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/aiUnkMessagePayloads.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {
class MessageAck;
struct MesTransceiverId;
}  // namespace ksys

namespace ksys::act {
class ActorLinkConstDataAccess;
class BaseProcLink;
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

struct Unk_71025be918Data;

// Unnamed message sender sub-objects embedded in many AI/Action/Behavior classes: they send a
// message of a fixed type from the owner actor's transceiver and record whether it was acknowledged.
// Placeholder names are the vtable addresses (Unk_<vtable>); unnamed non-virtual functions are named
// by address (sub_<addr>). The non-virtual functions live in the listener TU (0x7100708000-0x710070e300).

// vtable 0x7102357d20 (abstract)
class Unk_7102357d20 {
public:
    Unk_7102357d20(ksys::act::Actor* actor, u32 type)
        : _8(&actor->getMessageTransceiver()), _10(ksys::MessageType(type)) {}
    // PriestBossGiantEnemyRoot::_268: constructed without a transceiver (set by its init_).
    explicit Unk_7102357d20(u32 type) : _8(nullptr), _10(ksys::MessageType(type)) {}
    // The original keeps the base vtable store in every (inlined) destructor of this class, which a
    // defaulted destructor drops. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    virtual ~Unk_7102357d20() { ; }
    virtual void* m2() = 0;

    bool sub_710070DBB0(const ksys::MesTransceiverId& dest, bool ack);
    bool sub_710070DC38(ksys::act::Actor* actor, bool ack);
    bool sub_710070DCC0(ksys::act::BaseProcLink* link, bool ack);
    bool sub_710070DD78(const ksys::act::ActorLinkConstDataAccess& accessor, bool ack);
    bool sub_710070DE10(const ksys::MesTransceiverId& dest, bool ack);
    bool sub_710070DE98(ksys::act::Actor* actor, bool ack);
    bool sub_710070DF20(ksys::act::BaseProcLink* link, bool ack);
    bool sub_710070DFD8(const ksys::act::ActorLinkConstDataAccess& accessor, bool ack);
    bool sub_710070E070(const ksys::MessageAck& ack);

    ksys::MessageTransceiverBase* _8;
    ksys::MessageType _10;
    bool _14 = false;
};

// vtable 0x710235aba0: sends a BaseProcLink (message 0x8000040; payload in aiUnkMessagePayloads.h).
class Unk_710235aba0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    // Array element (AnchorSummon::_70): the transceiver is set after allocation.
    Unk_710235aba0() : Unk_7102357d20(0x8000040) {}
    void* m2() override { return &_18; }

    Unk_710235aba0_Payload _18;
};

// vtable 0x71023b73c8 (SendTargetActorRequestShareAwn::_30): sends a BaseProcLink (message 0x80000bf;
// same payload layout as Unk_710235aba0). Its out-of-line copies sit in actionSendMessageToTargetActor's TU.
class Unk_71023b73c8 : public Unk_7102357d20 {
public:
    Unk_71023b73c8(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        _18.y(actor);
    }
    void* m2() override { return &_18; }

    Unk_710235aba0_Payload _18;
};

// vtable 0x71023cd530 (WolfLinkAmiiboWarp::_28): sends message 0x80000a8 (a u32; payload in aiUnkMessagePayloads.h).
class Unk_71023cd530 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102450bb8_Payload _18;
};

// vtable 0x71023724e8 (Unk_7100711020 _28): sends message 0x8000010 (payload in
// aiUnkMessagePayloads.h). Its functions are next to Unk_7102372510's (0x71000e3430..).
class Unk_71023724e8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71024504c8_Payload _18;
};

// vtable 0x7102450c80 (Unk_7100711020 _80): sends message 0x800000f (payload in
// aiUnkMessagePayloads.h). Functions in the Unk_7100711020 TU (0x710071124c..).
class Unk_7102450c80 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102450c80_Payload _18;
};

// vtable 0x7102357d48 (DisableWeakPointActor behavior; functions next to the base's, 0x710001c2ec)
class Unk_7102357d48 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102357d70 (DisableWeakPointActor behavior; functions next to the base's, 0x710001c2f8)
class Unk_7102357d70 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710239c820 (HorseRideSearch::_40; message 0x3800007, no payload)
class Unk_710239c820 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710239b6b8 (HorseRideAngryGear1Coomand::_58; message 0x380000d, no payload)
class Unk_710239b6b8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710239bb28 (HorseRideCancelCommand::_58; message 0x380000a, no payload)
class Unk_710239bb28 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710239cca0 (HorseRideTurnCommand::_58; message 0x3800005): unit direction to the target
class Unk_710239cca0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &mLock; }

    sead::CriticalSection mLock;
    sead::Vector3f _58;
};

// vtable 0x710239c3a0 (HorseRideMoveToCommand::_98; message 0x3800003): the target position
class Unk_710239c3a0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &mLock; }

    // Inline only (HorseRideMoveToCommand::m32); placeholder name.
    void x(const sead::Vector3f& pos) {
        sead::ScopedLock<sead::CriticalSection> lock(&mLock);
        _58.set(pos);
    }

    sead::CriticalSection mLock;
    sead::Vector3f _58;
};

// vtable 0x710239bc68 (HorseRideChargeCommand::_98; message 0x3800006): the target actor
class Unk_710239bc68 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &mLock; }

    sead::CriticalSection mLock;
    ksys::act::BaseProcLink _58;
    s32 _68 = 0;
};

// vtable 0x710239bdc0 (HorseRideChaseCommand::_a0; message 0x3800008): the target actor and keep distance
class Unk_710239bdc0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &mLock; }

    sead::CriticalSection mLock;
    ksys::act::BaseProcLink _58;
    f32 _68 = 0;
};

// Non-virtual helper with the two senders above (ctor 0x710001bf60, dtor 0x710001bfd4; in this
// translation unit). Embedded in the GiantGuardWeakPoint behavior (0xa8). Placeholder name (ctor).
class Unk_710001bf60 {
public:
    explicit Unk_710001bf60(ksys::act::Actor* actor);
    ~Unk_710001bf60();

    // 0x710001c000 (lane4 s23): sets the AS slot, the "Tgt" physics body `tg_name`, the three AS names and the
    // partial bone part `data` (of the GiantPartBoneUnit). False if there is no part or actor.
    bool sub_710001C000(s32 slot, const sead::SafeString& tg_name, const sead::SafeString& start_as,
                        const sead::SafeString& loop_as, const sead::SafeString& end_as,
                        const sead::SafeString& partial_bone, Unk_71025be918Data* data);
    // 0x710001c0d8: starts the guard (state 1).
    void sub_710001C0D8();
    // 0x710001c13c: ends the guard (state 3).
    void sub_710001C13C();
    // 0x710001c194: stops the guard (state 0).
    void sub_710001C194();
    // 0x710001c1dc: advances the guard state (1 -> 2 -> 3 -> 0 when the AS slot finished the animation).
    void sub_710001C1DC();

    ksys::act::Actor* mActor;
    s32 _8 = 1;
    s32 _c = 0;
    sead::SafeString _10;
    sead::SafeString _20;
    sead::SafeString _30;
    Unk_7102357d48 _40;
    Unk_7102357d70 _58;
    ksys::phys::RigidBody* _70 = nullptr;
    Unk_71025be918Data* _78 = nullptr;
};

// vtable 0x7102396b20 (GolemSleepNormal)
class Unk_7102396b20 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102396b48 (GolemSleepNormal)
class Unk_7102396b48 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102411950 (PriestBossActorNormalRoot)
class Unk_7102411950 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18 = 0;
    ksys::act::BaseProcLink _20;
    u32 _30 = 0;
};

// vtable 0x7102418f20 (RemainsFireBattleMove)
class Unk_7102418f20 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// ---- Senders with JobQueueLock-guarded payloads (see aiUnkMessagePayloads.h) ----

// vtable 0x710237ecc0 (EventSendCatchWeaponMsgToPlayer, LumberjackTree); message 0x800001e
class Unk_710237ecc0 : public Unk_7102357d20 {
public:
    explicit Unk_710237ecc0(ksys::act::Actor* actor);
    void* m2() override { return &_18; }

    Unk_710237ecc0_Payload _18;
};

// vtable 0x71023f83e8; message 0x8000021
class Unk_71023f83e8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71023f83e8_Payload _18;
};

// vtable 0x71023b1608 (PullOut); message 0x800001b
class Unk_71023b1608 : public Unk_7102357d20 {
public:
    explicit Unk_71023b1608(ksys::act::Actor* actor);
    void* m2() override { return &_18; }

    Unk_71023b1608_Payload _18;
};

// vtable 0x7102411f48 (PriestBossBananaMode; D0/m2 at 0x71005101ec/0x71005101f0); message 0x80000d8
class Unk_7102411f48 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102411f48_Payload _18;
};

// vtable 0x71023dbd40 (PriestBossGiantDownSeq); message 0x80000d7
class Unk_71023dbd40 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71023dbd40_Payload _18;
};

// vtable 0x710236f520 (StalEnemyRoot; D2/D0/m2 at 0x71000d3e98..0x71000d425c); message 0x8000007
class Unk_710236f520 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_710236f520_Payload _18;
};

// vtable 0x71023eaec8 (EnemyRoot)
class Unk_71023eaec8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return _18; }

    ksys::act::BaseProcLink _18[2];
    sead::Matrix34f _38 = sead::Matrix34f::ident;
    u32 _68 = 0;
};

// vtable 0x7102396ae0 (StalPartNormal); message 0x800001f
class Unk_7102396ae0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102396ae0_Payload _18;
};

// vtable 0x71023b1860 (PriestBossCloneBulletRoot); message 0x80000d5
class Unk_71023b1860 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71023b1860_Payload _18;
};

// vtable 0x71023d4bb0 (AncientNecklaceBall; D2/D0/m2 at 0x71003015fc/0x710030254c/0x7100302580);
// message 0x80000ab
class Unk_71023d4bb0 : public Unk_7102357d20 {
public:
    explicit Unk_71023d4bb0(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x80000ab) {
        _18.y(actor);
    }
    void* m2() override { return &_18; }

    Unk_71023d4bb0_Payload _18;
};

// vtable 0x7102411178 (PriestBossActorEnemyRoot); message 0x80000dc
class Unk_7102411178 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102411178_Payload _18;
};

// vtable 0x7102413398 (PriestBossFormation); message 0x80000d3
class Unk_7102413398 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102413398_Payload _18;
};

// vtable 0x7102409958 (PriestBossMetaAIRoot); message 0x80000da
class Unk_7102409958 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    // PriestBossIronBall embeds an array of these and sets _8 afterwards.
    Unk_7102409958() : Unk_7102357d20(0x80000da) {}
    void* m2() override { return &_18; }

    Unk_7102409958_Payload _18;
};

// vtable 0x7102413c08 (PriestBossGiantStageRotate); message 0x80000de
class Unk_7102413c08 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Placeholder enum: the by-reference argument of sub_710070E2BC (a SEAD_ENUM temporary gets the
    // stack slot of the original's argument).
    SEAD_ENUM(Unk1, _0, _1)
    void sub_710070E2BC(const Unk1& a, s32 b);

    Unk_7102413c08_Payload _18;
};

// --- lane1 session 6 senders (merged by coordinator) ---
// vtable 0x71023ec318 (EnemyTreeWeaponSearchOrBattle)
class Unk_71023ec318 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x71023ec340 (EnemyTreeWeaponSearchOrBattle)
class Unk_71023ec340 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710239c018 (HorseRideChaseBattleAttackMove, HorseRideDynSetGearCommand, HorseRideMoveCommand):
// sends an int payload
class Unk_710239c018 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return reinterpret_cast<void*>(_18); }

    s32 _18 = 0;
};

// vtable 0x710239c040 (HorseRideChaseBattleAttackMove, HorseRideDynSetGearCommand, HorseRideMoveCommand)
class Unk_710239c040 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x71023eaef0 (EnemyRoot): the payload link is set to the owner actor on construction.
class Unk_71023eaef0 : public Unk_7102357d20 {
public:
    Unk_71023eaef0(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        _28.lock();
        _18.acquire(actor, false);
        _28.unlock();
    }
    void* m2() override { return &_18; }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x7102372510 (EnemyRecognizeTargetBase and ~20 others): sends a BaseProcLink (lock-guarded).
// Its functions are in another translation unit (0x71000e33f0..).
class Unk_7102372510 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x7102372d68 (DamageField::_60, Chemical::makeChmElementMaybe): sends message 0x8000084; the
// payload is the field type (2 by default). Its functions are in the DamageField TU (0x71000e61a0).
class Unk_7102372d68 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    s32 _18 = 2;
};

// vtable 0x71023d31f8 (AddBasicLinkOn, AddDemoCall, EnemyDemoSumonRecgTgt): sends a BaseProcLink
// (lock-guarded). Functions in the AddBasicLinkOn TU.
class Unk_71023d31f8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name (as Unk_7102372510::x).
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x71023e78b0 (EnemyFortressChat): same behaviour as Unk_71023eaef0.
class Unk_71023e78b0 : public Unk_7102357d20 {
public:
    Unk_71023e78b0(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        _28.lock();
        _18.acquire(actor, false);
        _28.unlock();
    }
    void* m2() override { return &_18; }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x710240bc48 (NPCTravelBase at +0x38, NPCMove at +0x2c0); message 0x8000009. D2 / D0 / m2 at
// 0x71004cdc50 / 0x71004d4f64 / 0x71004d4f98 (lane2 s21).
class Unk_710240bc48 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_710240bc48_Payload _18;
};

// --- lane1 session 7 senders ---
// vtable 0x710235abc8 (EnemyNormal); message 0x8000006. Its D2/D0/m2 are at 0x7100032a4c..
class Unk_710235abc8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_710235abc8_Payload _18;
};

// vtable 0x71023e8fd0 (EnemyNormal); message 0x80000c0 (payload declared as Unk_71023e7d28_Payload,
// named after its listener)
class Unk_71023e8fd0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71023e7d28_Payload _18;
};

// vtable 0x71023f31f8 (GerudoHeroSoulGiftRoot); no payload
class Unk_71023f31f8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102399748 (GerudoHeroSoulGiftRoot; functions at 0x710019a9ec..); message 0x800001d
class Unk_7102399748 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102399748_Payload _18;
};

// --- lane1 session 10 senders ---
// vtable 0x71023b0898 (CookPotRoot, DragonRoot, IceMakerBlock, PlayerAreaInOutSendMessage; functions
// at 0x710021d230..); message 0x8000083
class Unk_71023b0898 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_71023b0898_Payload _18;
};

// vtable 0x71023e7bc0 (MoveAndFreeFallGondola; functions at 0x71003906fc..); message 0x8000041 with
// a link to the sending actor (acquired in the constructor)
class Unk_71023e7bc0 : public Unk_7102357d20 {
public:
    Unk_71023e7bc0(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        _18.x(actor);
    }
    void* m2() override { return &_18; }

    Unk_71023e7bc0_Payload _18;
};

// vtable 0x7102368740 (functions in the AssassinBossIronBallAppear TU, 0x71000aa480..); message
// 0x8000037
class Unk_7102368740 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    // AssassinBossFirstBattle allocates an array of these and sets _8 afterwards.
    Unk_7102368740() : Unk_7102357d20(0x8000037) {}
    void* m2() override { return &_18; }

    Unk_7102368740_Payload _18;
};

// vtable 0x71024013b8 (Arrow; D0/m2 at 0x710046be74..); message 0x80000bb, no payload
class Unk_71024013b8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x71023f54b0 (GolemRoot; D0/m2 at 0x710040118c..); message 0x80000aa, no payload
class Unk_71023f54b0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102415900 (PriestBossPhaseThird; m2 0x710052d234, D0 0x710052d230); message 0x80000dd
class Unk_7102415900 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102415900_Payload _18;
};

// vtable 0x7102415df0 (PriestBossShadowCloneThrow: SafeArray of 8 at 0xb8; D2 0x710052f644, D0
// 0x710052f68c, m2 0x710052f6c8); message 0x80000d4. Default-constructed without a transceiver
// (PriestBossShadowCloneThrow::init_ sets _8).
class Unk_7102415df0 : public Unk_7102357d20 {
public:
    Unk_7102415df0() : Unk_7102357d20(0x80000d4) {}
    void* m2() override { return &_18; }

    Unk_7102450978_Payload _18;
};

// vtable 0x710242cb98 (TowingPlayer::_d8; D0 0x71005cd730, m2 0x71005cd734); message 0x8000025,
// no payload
class Unk_710242cb98 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710242cbc0 (TowingPlayer::_f0; D0 0x71005cd73c, m2 0x71005cd740); message 0x8000026,
// no payload
class Unk_710242cbc0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102410070 (PreyDead; D1/D0/m2 at 0x71004fa4ec / 0x71004fa52c / 0x71004fa560);
// message 0x80000a4
class Unk_7102410070 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102410070_Payload _18;
};

// The EnemyFortressChat action senders (lane3 s18): each carries a link to the owner actor,
// acquired in the constructor under the payload lock (as Unk_71023eaef0). Their D2 / D0 / m2 are in
// the action's own area (D2 64 B, D0 52 B, m2 8 B).

// vtable 0x7102379988 (EnemyFortressChatSpeak at +0xf0); message 0x800009e
class Unk_7102379988 : public Unk_7102357d20 {
public:
    Unk_7102379988(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        x(actor);
    }
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name (as Unk_7102372510::x).
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x7102379960 (EnemyFortressChatSpeak at +0x170); message 0x80000a2
class Unk_7102379960 : public Unk_7102357d20 {
public:
    Unk_7102379960(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        x(actor);
    }
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name (as Unk_7102372510::x).
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x71023796e0 (EnemyFortressChatCall at +0xf0); message 0x800009c
class Unk_71023796e0 : public Unk_7102357d20 {
public:
    Unk_71023796e0(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        x(actor);
    }
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name (as Unk_7102372510::x).
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x7102379c80 (EnemyFortressChatTurn at +0xd0); message 0x800009d
class Unk_7102379c80 : public Unk_7102357d20 {
public:
    Unk_7102379c80(ksys::act::Actor* actor, u32 type) : Unk_7102357d20(actor, type) {
        x(actor);
    }
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name (as Unk_7102372510::x).
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28);
        _18.acquire(proc, false);
    }

    ksys::act::BaseProcLink _18;
    sead::JobQueueLock _28;
};

// vtable 0x710244ffe8 (Unk_71006f3044 at +0x88); message 0x8000038 (no payload)
class Unk_710244ffe8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x710236acc8 / 0x710236acf0 (BasicSignalBossAwakeSleep at +0x20 / +0x38); messages 0x800007d /
// 0x800007e (no payload)
class Unk_710236acc8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class Unk_710236acf0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

// vtable 0x7102450010 (Unk_71006f3044 at +0xa0); message 0x8000039 (no payload)
class Unk_7102450010 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};
