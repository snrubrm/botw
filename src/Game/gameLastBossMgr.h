#pragma once

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
// around 0x71006774ac - 0x710067807c). The last boss (Ganon) manager; only the actor link at +0x550
// (spin lock at +0x564) that the GanonBeast AI registers its actor in is declared (lane4 s23); the
// constructor and everything else are not decompiled yet.
class LastBossMgr {
    // Stage unload calls the static teardown deleteInstance (0x710067775c).
    SEAD_SINGLETON_DISPOSER(LastBossMgr)
    // 0x71006777b4 (declared only)
    LastBossMgr();
    // declared only
    virtual ~LastBossMgr();

public:

    // 0x7100678108 (CSV LastBossMgr::postCalc; declared only).
    void postCalc();

    // 0x7100677ffc (CSV LastBossMgr::__auto1): stores `actor` in the link if it has none.
    void sub_7100677FFC(ksys::act::Actor* actor);
    // 0x7100677f24 (unnamed in the CSV; declared only): releases the entry that holds `actor` (under the
    // spin lock; Guardian's destructor).
    void sub_7100677F24(ksys::act::Actor* actor);
    // 0x710067807c: resets the link if it is `actor`.
    void sub_710067807C(ksys::act::Actor* actor);
    // lane1 s39: the registered actor link (read by GerudoHeroSoulGiftRoot::sub_71003F3154).
    ksys::act::BaseProcLink* getActorLink() { return &mActorLink; }
    // 0x7100035a90 tests isRegistered() on it before sending message 0xd8000000.
    ksys::MesTransceiverId& getMesTransceiverId() { return mMesTransceiverId; }

private:
    u8 _28[0x238 - 0x28];
    /* 0x238 */ ksys::MesTransceiverId mMesTransceiverId;
    u8 _250[0x550 - 0x250];
    /* 0x550 */ ksys::act::BaseProcLink mActorLink;
    u8 _560[4];
    /* 0x564 */ sead::JobQueueLock mLock;
};

KSYS_CHECK_SIZE_NX150(LastBossMgr, 0x568);

}  // namespace uking
