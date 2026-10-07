#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

namespace uking {

// Placeholder declaration (name from the CSV, namespace is a guess): created with `new (heap) (0xb0
// bytes)` by PlacementMgr::initAndStartPlacementThread (0x71011e5944, ctor 0x7100d5e674, init
// 0x7100d5e7f4) and stored in PlacementMgr + 0x218 (ksys::map::PlacementMgr::mVillagerMgr). It has a
// vtable (GOT 0x71025908e8), a critical section at 0x30 and a flag byte at 0x80 (bit 5 = disabled).
// Only the methods other code calls are declared (nothing is defined).
class VillagerMgr {
public:
    // 0x7100d5f9cc (CSV VillagerMgr::x_6): registers / updates the actor's villager entry (called by
    // KakarikoKokkoTimeline::enter_ with `true`; returns immediately when bit 5 of the flag byte is set).
    void x_6(ksys::act::Actor* actor, bool flag);
    // 0x7100d5eb2c (unnamed in the CSV; declaration only; lane5 s8): called by ksys::map::PlacementMgr::sub_71011E6E8C.
    void sub_7100D5EB2C();
};

}  // namespace uking
