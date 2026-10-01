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
    virtual ~Unk_7102357d20() = default;
    virtual void* m2() = 0;

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
// vtable 0x71023ec318 (EnemyTreeWeaponSearchOrBattle)
class Unk_71023ec318 : public Unk_7102357d20 {
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

    Unk_7102413c08_Payload _18;
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
