#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class BaseProc;
}  // namespace ksys::act

namespace ksys::phys {
class SystemGroupHandler;
}  // namespace ksys::phys

namespace uking {

// Name from the CSV (GearMgr::createInstance 0x7100668af8, GearMgr::ctor 0x7100668bd8, init,
// postCalc_). A polymorphic sead singleton (size 0x1108, instance pointer at 0x71025c5d08) with 0x80
// actor links (0x20-byte entries from +0x30) guarded by a CriticalSection at +0x1058. Only what the
// AI classes use is declared so far.
class GearMgr {
    SEAD_SINGLETON_DISPOSER(GearMgr)
    GearMgr();
    virtual ~GearMgr();

public:
    // Register / unregister `proc` (0x71006692f0 / 0x71006694b4: the actor links at +0x30;
    // 0x710066956c / 0x71006695dc: a second set). Placeholder names.
    void sub_71006692F0(ksys::act::BaseProc* proc, bool join_system_group);
    void sub_71006694B4(ksys::act::BaseProc* proc);
    void sub_710066956C(ksys::act::BaseProc* proc, bool join_system_group);
    void sub_71006695DC(ksys::act::BaseProc* proc);
    // 0x71006698b0: sets / clears bit 2 of the current entry's flags (+0x10a8, indexed by +0x28)
    // under the CriticalSection. Placeholder name.
    void sub_71006698B0(bool on);

    // Index (0 / 1) of the current entry of `_10a8`.
    s32 _28;
    u8 _2c[0x1050 - 0x2c];
    ksys::phys::SystemGroupHandler* _1050;
    u8 _1058[0x1098 - 0x1058];
    f32 _1098;  // read as a rotation offset by DgnObj_DLC_DungeonRotateTag
    u8 _109c[0x10a4 - 0x109c];
    // Bit 3 is tested by DgnObj_DLC_CWRotDirSwitch::calc_.
    u8 _10a4;
    u8 _10a5[3];
    // Two entries (current one: `_28`); bit 0 is read by DgnObj_DLC_CWRotDirSwitch::calc_ from the other
    // entry, bit 2 is set / cleared by sub_71006698B0.
    u32 _10a8[2];
    u8 _10b0[0x1108 - 0x10b0];
};
KSYS_CHECK_SIZE_NX150(GearMgr, 0x1108);

}  // namespace uking
