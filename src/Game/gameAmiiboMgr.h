#pragma once

#include <container/seadListImpl.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::act {
class Player;
}  // namespace ksys::act

namespace ksys::phys {
class CylinderRigidBody;
class QueryContactPointInfo;
}  // namespace ksys::phys

namespace uking {

// The amiibo that was last read, as stored in AmiiboMgr (+0x160) and copied by the AI / action
// classes that use it (ItemAmiiboRoot, ItemAmiiboSelectDropTable, WolfLinkAmiibo, ...). Placeholder
// name: the original type is unknown. `_0` / `_4` hold values of two SEAD_ENUM-like amiibo id enums
// (their value tables are built by 0x1c08ac / 0x1c1a40), `_8` is a 0x104-byte block of the amiibo's
// data, `mName` the amiibo's name.
struct AmiiboInfo {
    u32 _0 = 0;
    u32 _4 = 0;
    u8 _8[0x104]{};
    sead::FixedSafeString<48> mName;
};
KSYS_CHECK_SIZE_NX150(AmiiboInfo, 0x158);

// The listener registered with the NFP thread (vtable 0x710243b770; embedded in AmiiboMgr at
// +0x148). Placeholder name = vtable address. Its callback slot is named spawnAmiiboRuneActor in the
// CSV (0x7100648a2c). The list node is a base class: the inlined constructor in createInstance
// clears its two pointers before it stores the vtable.
class Unk_710243b770 : public sead::ListNode {
public:
    virtual ~Unk_710243b770() {}
    // `name`: the amiibo's name; `ids[0]` / `ids[2]` become `mInfo._0` / `mInfo._4`; `data` is the
    // amiibo's 0x104-byte data block.
    virtual void spawnAmiiboRuneActor(const sead::SafeString& name, const u32* ids, const u8* data);
    virtual void m3() {}

    AmiiboInfo mInfo;
};
KSYS_CHECK_SIZE_NX150(Unk_710243b770, 0x170);

// Name from the CSV (AmiiboMgr::createInstance 0x71006488a8, init, isAmiiboAllowed, ...). The
// amiibo manager singleton (instance 0x71025bf378, 0x2d0 bytes). Layout from the inlined
// constructor in createInstance and the destructor 0x7100648e70.
class AmiiboMgr : public ksys::ActorMessageTransceiver::IHandler, public Unk_710243c330 {
    SEAD_SINGLETON_DISPOSER(AmiiboMgr)
    AmiiboMgr();
    ~AmiiboMgr() override;

public:
    int handleMessage(const ksys::Message& message) override { return 1; }

    // 0x7100648e58 / 0x7100648e60 / 0x7100648e68 (CSV names): constant `false`.
    bool guaranteedBigHits() const;
    bool guaranteedGreatHits() const;
    bool guaranteedEpona() const;
    // 0x710064a200 (CSV name): constant `false`.
    bool noAmiiboUseLimit() const;

    // GameScene::initialize: creates the amiibo marker collision (cylinder + contact point info).
    bool init(sead::Heap* heap);

    // Checks the "IsPlayed_Demo14x" / "NakedIsland_ProhibitAmiibo" game data flags.
    bool isAmiiboAllowed();
    bool isMotorcycleAllowed();

    // 0x710064978c (CSV __auto0): per-frame update, called from Player::calcMaybe.
    void sub_710064978C(ksys::act::Player* player);
    // 0x710064999c (CSV x): the amiibo marker / scan logic (state `_a8`, `_b0` / `_d0` effects).
    void sub_710064999C(ksys::act::Player* player);
    // 0x7100648ca4: called by spawnAmiiboRuneActor when an amiibo was read.
    void sub_7100648CA4();
    // 0x7100649f94: fades the marker effect `_b0`, resets `_a8`, `_90` and the sound handle.
    void sub_7100649F94();
    // 0x710064a0a0: updates `_134` bits 4 / 5 from the NFP state.
    void sub_710064A0A0();

    // True if the last amiibo use was on another day (nn::time + AmiiboLastTouchDate).
    bool oneDayHasPassed();
    // Adds `info` to the "AmiiboTouchHistory" / "AmiiboTouchHistoryTotal" game data string arrays and
    // stores the current date as AmiiboLastTouchDate.
    void registerAmiibo(const AmiiboInfo& info);
    // 0x710064b680: `key` is the string array flag name; `today` is oneDayHasPassed().
    void addAmiiboToHistory(const AmiiboInfo& info, const sead::SafeString& key, bool today);
    // `mode` 0-3 selects what is compared (name / ids). Returns the matching entry's count.
    int queryHistory(const AmiiboInfo& info, const sead::SafeString& key, u32 mode);
    int queryHistoryToday(const AmiiboInfo& info, u32 mode);
    bool queryHistoryTodayWithWorldMgrCheck(const AmiiboInfo& info, u32 mode);
    int queryHistoryTotal(const AmiiboInfo& info, u32 mode);
    // 0x710064ac8c: resets the use count of `info` in `key` (ItemAmiiboCreateFromDropTable::enter_).
    void resetUseCount(const AmiiboInfo& info, const sead::SafeString& key, bool a);

    /* 0x038 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    /* 0x090 */ sead::Vector3f _90{0, 0, 0};
    /* 0x09c */ sead::Vector3f _9c;
    /* 0x0a8 */ s32 _a8 = 0;  // marker state: 0 none, 1 OK, 2 NG, 3 NG (too far)
    /* 0x0b0 */ Unk_71012419b4 _b0;
    /* 0x0d0 */ Unk_71012419b4 _d0;
    /* 0x0f0 */ sead::CriticalSection mCS;
    /* 0x130 */ s32 _130 = 0;
    // Bit 0: marker active, bit 2: listener registered, bit 3: amiibo read, bit 4 / 5: NFP checks,
    // bit 6: amiibo allowed.
    /* 0x134 */ u8 _134 = 0;
    /* 0x138 */ ksys::phys::CylinderRigidBody* _138 = nullptr;
    /* 0x140 */ ksys::phys::QueryContactPointInfo* _140 = nullptr;
    /* 0x148 */ Unk_710243b770 _148;
    /* 0x2b8 */ xlink2::HandleSLink _2b8;
    /* 0x2c8 */ s32 _2c8 = 0;
    /* 0x2cc */ s32 _2cc = 0;
};
KSYS_CHECK_SIZE_NX150(AmiiboMgr, 0x2d0);

}  // namespace uking
