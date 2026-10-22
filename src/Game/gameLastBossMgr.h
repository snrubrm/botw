#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadJobQueue.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// Name from the CSV (LastBossMgr::__auto1 0x7100677ffc; the instance pointer is 0x71025c5dd0, the TU is
// around 0x71006774ac - 0x710067807c). The last boss (Ganon) manager. It keeps the GanonBeast actor
// link at +0x550 and 32 slots (a link and a message transceiver id each) for the boss's parts.
class LastBossMgr {
    // Stage unload calls the static teardown deleteInstance (0x710067775c).
    SEAD_SINGLETON_DISPOSER(LastBossMgr)
    // 0x71006777b4
    LastBossMgr();
    // 0x7100677ac0 (D1), 0x7100677e34 (D0)
    virtual ~LastBossMgr();

public:

    // 0x7100678108 (CSV LastBossMgr::postCalc): drops the message ids of the empty slots.
    void postCalc();

    // 0x7100677ffc (CSV LastBossMgr::__auto1): stores `actor` in the link if it has none.
    void sub_7100677FFC(ksys::act::Actor* actor);
    // 0x7100677f24 (unnamed in the CSV): releases the slot that holds `actor` (under the spin lock;
    // Guardian's destructor).
    void sub_7100677F24(ksys::act::Actor* actor);
    // 0x7100677e58 (unnamed in the CSV): acquires the first free slot for `actor` and copies its
    // message id.
    void sub_7100677E58(ksys::act::Actor* actor);
    // 0x710067807c: resets the link if it is `actor`.
    void sub_710067807C(ksys::act::Actor* actor);
    // lane1 s39: the registered actor link (read by GerudoHeroSoulGiftRoot::sub_71003F3154).
    ksys::act::BaseProcLink* getActorLink() { return &mActorLink; }
    // 0x7100035a90 tests isRegistered() on it before sending message 0xd8000000.
    ksys::MesTransceiverId& getMesTransceiverId() { return mMesTransceiverId; }

private:
    // Resets the boss link, the slots and their message ids (inline in the destructor).
    void clear();

    // The current boss actor link; its message id is reset by postCalc when the link is empty.
    /* 0x028 */ ksys::act::BaseProcLink mBossLink;
    // The slots' actor links.
    /* 0x038 */ sead::SafeArray<ksys::act::BaseProcLink, 32> mLinks;
    /* 0x238 */ ksys::MesTransceiverId mMesTransceiverId;
    // The slots' message ids (parallel to mLinks).
    /* 0x250 */ sead::SafeArray<ksys::MesTransceiverId, 32> mLinkIds;
    /* 0x550 */ ksys::act::BaseProcLink mActorLink;
    /* 0x560 */ u16 _560;
    /* 0x564 */ sead::JobQueueLock mLock;
};

KSYS_CHECK_SIZE_NX150(LastBossMgr, 0x568);

}  // namespace uking
