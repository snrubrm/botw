#pragma once

#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class PlayerBase;
}  // namespace ksys::act

namespace uking {

// Name from the CSV (RuneMgr::createInstance 0x7100674f78, ctor 0x7100675000, setHandled, setCurrentItem,
// checkIsSelectedRuneAndCanUse, ...; the TU is 0x7100674bc0-0x71006774ac). The Sheikah slate rune
// manager singleton (instance 0x71025c5da8, 0x428 bytes; vtable 0x710243c408 with the same three
// bases as AmiiboMgr / IceBlockMgr). Only what the player / AI / UI code uses is declared; the
// constructor, destructors and most members are not decompiled yet.
//
// The rune indices (`checkCanUseRune`, `isSelectedRune`, PlayerBase::runeMgrCheckCanUse*): 0 round
// bomb, 1 square bomb, 2 magnesis, 3 stasis (StasisMgr), 4 cryonis, 5 camera, 6 amiibo, 7 motorcycle.
class RuneMgr : public ksys::ActorMessageTransceiver::IHandler, public Unk_710243c330 {
    SEAD_SINGLETON_DISPOSER(RuneMgr)
    RuneMgr();
    ~RuneMgr() override;

public:
    int handleMessage(const ksys::Message& message) override;

    // A flag that is set / read under its own critical section (the five at 0x98..0x1f8: 0x98 /
    // 0xe0 / 0x128 / 0x170 / 0x1b8; the sixth critical section at 0x200 guards the current item).
    struct LockedFlag {
        sead::CriticalSection mCS;
        bool mFlag = false;
    };

    // CSV names: setFieldD8 (0x7100675848; sets the flag of `_98`), setHandled (0x7100675918; `_128`),
    // setFlag1F8 (0x71006758e4; `_1b8`). The others are unnamed (placeholder names).
    void setFieldD8();
    void sub_710067587C();  // `_e0`
    void sub_71006758B0();  // `_e0` (a second copy of the same code)
    void setHandled();
    void sub_710067594C();  // `_170` (CSV __auto5)
    void setFlag1F8();

    s32 getCurrentItem();
    void setCurrentItem(s32 item);

    // 0x710067622c: whether the selected rune (`_248`) is `rune`.
    bool isSelectedRune(s32 rune) const;
    // 0x7100676214: `_248 == rune && checkCanUseRune(rune, player)`.
    bool checkIsSelectedRuneAndCanUse(s32 rune, ksys::act::PlayerBase* player);
    // 0x710067613c: dispatches on `rune` to the player's checkCanUse* (the current player when
    // `player` is null).
    bool checkCanUseRune(s32 rune, ksys::act::PlayerBase* player);

    // 0x710067525c (CSV __auto6): byte flag at 0x250.
    bool sub_710067525C() const;

    /* 0x038 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    /* 0x090 */ u32 _90 = 0;  // flags (bit 4: camera selected ..., bit 7 / 8: remote bomb state)
    /* 0x094 */ u32 _94 = 0;
    /* 0x098 */ LockedFlag _98;
    /* 0x0e0 */ LockedFlag _e0;
    /* 0x128 */ LockedFlag _128;
    /* 0x170 */ LockedFlag _170;
    /* 0x1b8 */ LockedFlag _1b8;
    /* 0x200 */ sead::CriticalSection _200;
    /* 0x240 */ s32 _240;  // current item (guarded by `_200`)
    /* 0x244 */ u8 _244[4];
    /* 0x248 */ s32 _248;  // selected rune (-1: none)
    /* 0x24c */ s32 _24c;
    /* 0x250 */ bool _250;
    /* 0x251 */ u8 _251[0x428 - 0x251];
};
KSYS_CHECK_SIZE_NX150(RuneMgr, 0x428);

}  // namespace uking
