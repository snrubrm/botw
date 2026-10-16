#pragma once

#include <math/seadVector.h>

#include "Game/UI/uiTimer.h"

#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "Game/gameUnk_710243c330.h"
#include "Game/gameGraphics.h"
#include "Game/gameUnk_710243c698.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace uking::act {
class PlayerBase;
}

namespace ksys::act {
class Actor;
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
    // 0x71006775fc.
    int handleMessage(const ksys::Message* message) override { return 1; }

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

    // 0x7100676104 (lane4 s64; placeholder name): reads the equipped item type game data (-1 when it is above 7) into
    // _248, _24c and _240.
    s32 sub_7100676104();
    s32 getCurrentItem();
    void setCurrentItem(s32 item);

    // 0x710067622c: whether the selected rune (`_248`) is `rune`.
    bool isSelectedRune(s32 rune) const;
    // 0x7100676214: `_248 == rune && checkCanUseRune(rune, player)`.
    bool checkIsSelectedRuneAndCanUse(s32 rune, uking::act::PlayerBase* player);
    // 0x710067613c: dispatches on `rune` to the player's checkCanUse* (the current player when
    // `player` is null).
    bool checkCanUseRune(s32 rune, uking::act::PlayerBase* player);

    // 0x71006757b8 (CSV __auto0; declared only, lane2 s46): sets the duration (1e-4) of the two UiTimers at 0x3c8 / 0x3e0.
    void sub_71006757B8();

    // 0x710067623c (placeholder name): stores `value` in _2a0 and _28c.
    void sub_710067623C(const sead::Vector2f& value);
    // 0x710067549c / 0x71006754a4 (placeholder names): float getters.
    f32 sub_710067549C() const;
    f32 sub_71006754A4() const;
    // Forwarders to the remote bomb tracker _2a8 (0x71006754ac CSV __auto3, 0x71006754b4 CSV __auto12,
    // 0x71006754cc CSV __auto10, 0x71006754d8 CSV __auto1; spawnBomb is the CSV name).
    void sub_71006754AC();
    void sub_71006754B4();
    ksys::act::Actor* spawnBomb(u8 idx, const sead::Matrix34f& mtx, s32 type, bool a4);
    bool sub_71006754CC(u8 idx);
    void sub_71006754D8(u8 idx);
    // 0x71006754e4 (CSV x_1): sub_710067EC28 with the actor's position.
    f32 sub_71006754E4(u8 idx, const ksys::act::Actor* actor);
    // 0x7100675520 (CSV __auto2) / 0x710067552c / 0x710067557c (CSV __auto7): sub_710067E4E0, and when it
    // succeeds bit 0 / bit 3 of the entry flags.
    bool sub_7100675520(u8 idx);
    bool sub_710067552C(u8 idx);
    bool sub_710067557C(u8 idx);

    // 0x710067525c (CSV __auto6): byte flag at 0x250.
    bool sub_710067525C() const;
    // 0x71006752ac (CSV RuneMgr::__auto11; placeholder name): updates the target actors (x_0), then returns
    // _408 while _90 bit 8 is set, nothing while bit 7 is set, else _410. StasisMgr::__auto1 uses it as
    // the stasis target candidate.
    ksys::act::Actor* sub_71006752AC();
    // 0x71006752f0 (CSV name; declaration only): updates _408 / _410 from the object at _258 (calls
    // sead::MemUtil::checkFillType and compares the result with 2, which our sead declares as bool).
    void x_0();

    // 0x71006757f8 (CSV __auto15; placeholder name): whether UiTimer _3c8[idx]
    // (idx clamped to 0-1) is done.
    bool __auto15(int idx);
    // 0x710067582c (placeholder name): the progress of the UiTimer `_3c8[idx]` (idx clamped to 0-1).
    f32 sub_710067582C(int idx) const;

    /* 0x038 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    /* 0x090 */ u32 _90 = 0;  // flags (bit 4: camera selected ..., bit 7 / 8: remote bomb state)
    /* 0x094 */ u32 _94 = 0;
    /* 0x098 */ LockedFlag _98;
    /* 0x0e0 */ LockedFlag _e0;
    /* 0x128 */ LockedFlag _128;
    /* 0x170 */ LockedFlag _170;
    /* 0x1b8 */ LockedFlag _1b8;
    /* 0x200 */ sead::CriticalSection _200;
    /* 0x240 */ s32 _240 = 0;  // current item (guarded by `_200`)
    /* 0x244 */ u8 _244[4];
    /* 0x248 */ s32 _248 = -1;  // selected rune (-1: none)
    /* 0x24c */ s32 _24c = -1;
    // Constructed by the RuneMgr ctor; the dtor unregisters it from Graphics (sub_7100F2F1E8) when
    // it is the current one. _30 is returned by sub_71006754A4, _4c by sub_710067549C; _3c / _40
    // are set with _2a0 by sub_710067623C.
    /* 0x250 */ Unk_7100f35df8 _250;
    /* 0x2a0 */ sead::Vector2f _2a0{0, 0};
    // The remote bomb tracker (constructed at +0x2a8 by the RuneMgr constructor 0x7100675000).
    /* 0x2a8 */ Unk_710243c698 _2a8;
    // The two UiTimers set by sub_71006757B8 (0x18 bytes each).
    /* 0x3c8 */ ui::UiTimer _3c8[2];
    // Set by the ctor body (no initializer).
    /* 0x3f8 */ void* _3f8;
    /* 0x400 */ void* _400;
    // Actors from the object at _258 (x_0 0x71006752f0 tests them with hasTag; the dtor clears both).
    /* 0x408 */ ksys::act::Actor* _408 = nullptr;
    /* 0x410 */ ksys::act::Actor* _410 = nullptr;
    /* 0x418 */ f32 _418 = -1.0f;
    /* 0x41c */ f32 _41c = -1.0f;
    /* 0x420 */ f32 _420 = -1.0f;
};
KSYS_CHECK_SIZE_NX150(RuneMgr, 0x428);

}  // namespace uking
