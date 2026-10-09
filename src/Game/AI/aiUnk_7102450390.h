#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "Game/AI/aiUnk_71025afb58.h"

namespace ksys {
class Message;
class MessageAck;
}  // namespace ksys

namespace ksys::act {
class Actor;
namespace ai {
class Ai;
}
}  // namespace ksys::act

// Placeholder (vtable 0x7102450390: shared AI-tree RTTI subtype, D1 0x7100705978 (664 B), D0 0x7100705cac) for the 0x308-byte message
// handling composite embedded in ForestGiantRoot at +0x230 (ctor 0x7100705834; the object at +0x150 has its own
// vtable 0x71024503c0). Only the members that ForestGiantRoot calls are declared (all declaration only).
// Constructor vtable slots and the necklace caller prove this shared AI-tree RTTI subtype.
class Unk_7102450390 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450390, Unk_71025afb58)
public:
    // 0x7100705834
    explicit Unk_7102450390(ksys::act::Actor* actor);
    // 0x7100705978
    ~Unk_7102450390() override;

    // 0x7100707544: drops the selected necklace slot; implementation remains declared-only.
    void sub_7100707544(s32 slot);

    void sub_71007062D4();
    ksys::act::Actor* sub_7100706D0C(u32 slot);

    // 0x7100706c3c: called by leave_.
    void sub_7100706C3C();
    // 0x7100706e98: called by loadParams_ with the owner AI.
    void sub_7100706E98(ksys::act::ai::Ai* owner);
    // 0x7100707224: tried first by handleMessage_.
    bool sub_7100707224(const ksys::Message* message);
    // 0x71007073d0: called by handleAck_.
    bool sub_71007073D0(const ksys::MessageAck* ack);

private:
    // Constructor 705834 and helpers 7062D4 / 706C3C prove the actor and timer/link tail.
    /* 0x008 */ ksys::act::Actor* mActor;
    u8 _10[0x2c0 - 0x10];
    /* 0x2c0 */ bool _2c0;
    u8 _2c1[3];
    /* 0x2c4 */ s32 _2c4;
    /* 0x2c8 */ s32 _2c8;
    /* 0x2cc */ ksys::Timer _2cc;
    /* 0x2d8 */ ksys::act::BaseProcLink _2d8;
    /* 0x2e8 */ ksys::act::BaseProcHandle _2e8;
    /* 0x2f8 */ ksys::Timer _2f8;
};
static_assert(sizeof(Unk_7102450390) == 0x308);
