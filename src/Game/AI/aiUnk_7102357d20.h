#pragma once

#include <basis/seadTypes.h>
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

// Unnamed message sender sub-objects embedded in many AI/Action/Behavior classes: they send a
// message of a fixed type from the owner actor's transceiver and record whether it was acknowledged.
// Placeholder names are the vtable addresses (Unk_<vtable>); unnamed non-virtual functions are named
// by address (sub_<addr>). The non-virtual functions live in the listener TU (0x7100708000-0x710070e300).

// vtable 0x7102357d20 (abstract)
class Unk_7102357d20 {
public:
    Unk_7102357d20(ksys::act::Actor* actor, u32 type)
        : _8(&actor->getMessageTransceiver()), _10(type) {}
    // PriestBossGiantEnemyRoot::_268: constructed without a transceiver (set by its init_).
    explicit Unk_7102357d20(u32 type) : _8(nullptr), _10(type) {}
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
    void* m2() override { return &_18; }

    Unk_710235aba0_Payload _18;
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
    void* m2() override { return &_18; }

    Unk_7102409958_Payload _18;
};

// vtable 0x7102413c08 (PriestBossGiantStageRotate); message 0x80000de
class Unk_7102413c08 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    void sub_710070E2BC(const u32& a, s32 b);

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

// vtable 0x71023d31f8 (AddBasicLinkOn, AddDemoCall, EnemyDemoSumonRecgTgt): sends a BaseProcLink
// (lock-guarded). Functions in the AddBasicLinkOn TU.
class Unk_71023d31f8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

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
