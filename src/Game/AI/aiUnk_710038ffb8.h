#pragma once

#include <basis/seadTypes.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

// Placeholder (size 0x3d0; embedded at EnemyFortressWait + 0x70 and EnemyFortressWatchKeepingWait + 0x80; ctor
// 0x710038ffb8 (an owner pointer, the init arg and a set of message senders / listeners with BaseProcLinks), unnamed).
// Message subobjects follow the full constructor, destructor and independent message consumers.
class Unk_710038ffb8 {
public:
    // 0x710038ffb8 (1136 B, declared only): stores the owner and constructs actor message subobjects.
    Unk_710038ffb8(const ksys::act::ai::ActionBase::InitArg& arg, ksys::act::ai::Ai* owner);
    // 0x7100390428: ordinary member destruction resets the message links and IDs.
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
    void sub_71003910E4();
    void sub_71003916F4();
    void sub_710039184C();
    void sub_7100391A10();
    void sub_7100391B5C();
    // 0x710039235c: the message handler (2532 B).
    bool sub_710039235C(const ksys::Message& message);

    // The link that EnemyFortressWait::enter_ sets to its target actor.
    ksys::act::BaseProcLink& getTargetLink() { return _3a0; }

private:
    // A flag byte somewhere else that sub_7100390A90 clears (what it belongs to is unknown).
    bool* _8;
    ksys::act::ai::Ai* _10;
    const s32* _18;
    const s32* _20;
    const s32* _28;
    const s32* _30;
    const s32* _38;
    const s32* _40;
    const s32* _48;
    sead::SafeString _50;
    // The complete constructor and lifetime pair identify these message subobjects.
    /* 0x60 */ Unk_71023e7c38 _60;
    /* 0xb0 */ Unk_71023e7c68 _b0;
    /* 0x100 */ Unk_71023e7c98 _100;
    /* 0x150 */ Unk_71023e7c10 _150;
    /* 0x180 */ Unk_71023e7cc8 _180;
    /* 0x1d0 */ Unk_71023e7be8 _1d0;
    /* 0x200 */ Unk_7102450708 _200;
    /* 0x250 */ Unk_710235aba0 _250;
    /* 0x280 */ Unk_71023e7bc0 _280;
    /* 0x2b0 */ Unk_71023e7cf8 _2b0;
    /* 0x300 */ Unk_71023e7b98 _300;
    /* 0x330 */ Unk_71023e7d28 _330;
    /* 0x378 */ ksys::MesTransceiverId _378;
    /* 0x390 */ ksys::act::BaseProcLink _390;
    /* 0x3a0 */ ksys::act::BaseProcLink _3a0;
    f32 _3b0;
    f32 _3b4;
    u8 _3b8[0x3c8 - 0x3b8];

public:
    // Flags written by sub_7100390A90 (= 0x10) and read by sub_7100390ABC (bits 2 and 4); the owners
    // (EnemyFortressWait, EnemyFortressWatchKeepingWait) use bit 0 (changeable), bit 3 and bit 5 inline.
    /* 0x3c8 */ u8 _3c8;
    u8 _3c9[0x3d0 - 0x3c9];
};
KSYS_CHECK_SIZE_NX150(Unk_710038ffb8, 0x3d0);
