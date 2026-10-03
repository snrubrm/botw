#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class Message;
class MessageAck;
}  // namespace ksys

// Placeholder name: the non-polymorphic data class that Unk_71025b1808 holds at +8 (a member: the
// vtable store comes before its constructor) (RTTI static 0x71025b1808; shared by the EnemyFortress AI/Action classes through the
// "RegistedActorUnit" AI tree variable; RegistedActorActionBase embeds it at +0x20). It keeps up to 32
// registered actors, broadcasts a message (0x8000040) to them and registers new actors from
// messages. Functions: 0x7100efe9c / 0x71006f0090 (ctors), 0x71006f0178 (dtor), 0x71006f0354..0x71006f0734.
// Size 0x3e0.
class Unk_71025b1808Data {
public:
    // Default constructor: no owner / transceiver yet (EnemyFortressMgrTag::init_ sets them).
    Unk_71025b1808Data();
    // With the owner actor (also the sender's transceiver).
    explicit Unk_71025b1808Data(ksys::act::Actor* actor);
    ~Unk_71025b1808Data();

    // 0x71006f0354 (EnemyFortressMgrTag::enter_ passes false): the payload link is set to the owner
    // actor (under the lock) and `_3d8` to `enabled`. Placeholder name.
    void sub_71006F0354(bool enabled);
    // 0x71006f03d0 (EnemyFortressMgrTag::calc_): if enabled, sends the message to every registered
    // actor that has not acknowledged it yet.
    void sub_71006F03D0();
    // 0x71006f0448 (handleMessage_): registers the actor of a 0x8000040 message (and remembers the
    // 0x8000041 one); false when all 32 slots are in use.
    bool sub_71006F0448(const ksys::Message& message);
    // 0x71006f0604 (handleAck_): marks the registered actor that acknowledged the message.
    bool sub_71006F0604(const ksys::MessageAck& ack);
    // 0x71006f0734: sends `type` / `data` from the owner to every registered actor.
    void sub_71006F0734(const ksys::MessageType& type, void* data);

    struct Entry {
        ksys::act::BaseProcLink link;
        bool _10;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x18);

    /* 0x000 */ Unk_710235aba0 mSender;
    /* 0x030 */ sead::SafeArray<Entry, 32> mEntries;
    /* 0x330 */ ksys::act::Actor* mOwner;
    /* 0x338 */ Unk_7102450ac8 _338;
    /* 0x388 */ Unk_710235cec8 _388;
    /* 0x3d8 */ bool _3d8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71025b1808Data, 0x3e0);

// RTTI static 0x71025b1808 (parent: Unk_71025afb58): the object the "RegistedActorUnit" AI tree
// variable points to (EnemyFortressMgrTag embeds it at +0x50). Its destructors / RTTI functions are
// inline (the executable has one copy in EnemyFortressMgrTag's area, 0x710038e90c..).
class Unk_71025b1808 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b1808, Unk_71025afb58)
public:
    Unk_71025b1808() = default;
    ~Unk_71025b1808() override = default;

    /* 0x08 */ Unk_71025b1808Data _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71025b1808, 0x3e8);
