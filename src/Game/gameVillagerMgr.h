#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/physLayerMaskBuilder.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys { class RayCastForRequest; }

namespace ksys::act {
class Actor;
}

namespace uking {

// Placeholder declaration (name from the CSV, namespace is a guess): created with `new (heap) (0xb0
// bytes)` by PlacementMgr::initAndStartPlacementThread (0x71011e5944, ctor 0x7100d5e674, init
// 0x7100d5e7f4) and stored in PlacementMgr + 0x218 (ksys::map::PlacementMgr::mVillagerMgr). It has a
// vtable (GOT 0x710259b8e8), a critical section at 0x30 and a flag byte at 0x80 (bit 5 = disabled).
class VillagerMgr {
public:
    explicit VillagerMgr(const sead::Vector3f& pos);
    virtual ~VillagerMgr();
    void init(sead::Heap* heap);

    // 0x7100d5f9cc (CSV VillagerMgr::x_6): registers / updates the actor's villager entry (called by
    // KakarikoKokkoTimeline::enter_ with `true`; returns immediately when bit 5 of the flag byte is set).
    void x_6(ksys::act::Actor* actor, bool flag);
    // 0x7100d5eb2c (unnamed in the CSV; declaration only; lane5 s8): called by ksys::map::PlacementMgr::sub_71011E6E8C.
    void sub_7100D5EB2C();

private:
    struct Entry {
        s32 _0 = -1;
        ksys::phys::RayCastForRequest* mRayCast = nullptr;
    };
    sead::OffsetList<ksys::act::Actor> mActors;
    sead::Buffer<Entry> mEntries;
    sead::CriticalSection mCS;
    sead::Vector3f mPos;
    s32 _7c = 0;
    u8 mFlags = 0;
    u8 _81[7];
    ksys::phys::LayerMaskBuilder mLayerMasks;
    void* _a0 = nullptr;
    s32 _a8 = 0;
};
KSYS_CHECK_SIZE_NX150(VillagerMgr, 0xb0);

}  // namespace uking
