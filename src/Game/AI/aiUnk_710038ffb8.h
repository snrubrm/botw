#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

// Placeholder (size 0x3d0; embedded at EnemyFortressWait + 0x70 and EnemyFortressWatchKeepingWait + 0x80; ctor
// 0x710038ffb8 (an owner pointer, the init arg and a set of message senders / listeners with BaseProcLinks), unnamed).
// Only the members that those two classes call are declared (all declaration only).
class Unk_710038ffb8 {
public:
    // 0x710038ffb8 (1136 B, declared only): the owner AI and the init arg of the owner are stored in the object.
    Unk_710038ffb8(const ksys::act::ai::ActionBase::InitArg& arg, ksys::act::ai::Ai* owner);
    // 0x7100390428 (540 B, declared only): resets the BaseProcLinks of the message senders / listeners.
    virtual ~Unk_710038ffb8();

    // 0x7100390930: called by init_ (352 B).
    bool sub_7100390930(sead::Heap* heap);
    // 0x7100390a90: called by enter_.
    s32 sub_7100390A90();
    // 0x7100390abc: called by calc_ (592 B).
    void sub_7100390ABC();
    // 0x7100390d0c / 0x7100391230: the per-state updates of calc_ (result 1: stay, 2: change to wait).
    s32 sub_7100390D0C();
    s32 sub_7100391230();
    // 0x7100392044: called by leave_.
    void sub_7100392044();
    // 0x7100392230: called by loadParams_.
    void sub_7100392230();
    // 0x710039235c: the message handler (2532 B).
    bool sub_710039235C(const ksys::Message& message);

    // The link that EnemyFortressWait::enter_ sets to its target actor.
    ksys::act::BaseProcLink& getTargetLink() { return _3a0; }

private:
    // A flag byte somewhere else that sub_7100390A90 clears (what it belongs to is unknown).
    u8* _8;
    void* _10[(0x3a0 - 0x10) / sizeof(void*)];
    /* 0x3a0 */ ksys::act::BaseProcLink _3a0;
    void* _3b0[(0x3c8 - 0x3b0) / sizeof(void*)];

public:
    // Flags written by sub_7100390A90 (= 0x10) and read by sub_7100390ABC (bits 2 and 4); the owners
    // (EnemyFortressWait, EnemyFortressWatchKeepingWait) use bit 0 (changeable), bit 3 and bit 5 inline.
    /* 0x3c8 */ u8 _3c8;
    u8 _3c9[0x3d0 - 0x3c9];
};
KSYS_CHECK_SIZE_NX150(Unk_710038ffb8, 0x3d0);
