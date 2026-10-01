#pragma once

#include <basis/seadTypes.h>
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

// vtable 0x710235aba0: sends a BaseProcLink; _28 guards _18 (spin lock, see sub_710070E194 / sub_710070E1F8).
class Unk_710235aba0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    ksys::act::BaseProcLink _18;
    u32 _28 = 0;
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
