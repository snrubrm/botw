#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
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
    // 0x7100669ee0 (CSV GearMgr::postCalc; declared only).
    void postCalc();
    // Register / unregister `proc` (0x71006692f0 / 0x71006694b4: the actor links at +0x30;
    // 0x710066956c / 0x71006695dc: a second set). Placeholder names.
    void sub_71006692F0(ksys::act::Actor* actor, bool join_system_group);
    void sub_71006694B4(ksys::act::Actor* actor);
    void sub_710066956C(ksys::act::BaseProc* proc, bool join_system_group);
    void sub_71006695DC(ksys::act::BaseProc* proc);
    // 0x7100669144 (lane1 s22; the CSV name is a mislabel): registers a gear ratio (updates the lcm
    // kept at +0x10c8). Placeholder name.
    void sub_7100669144(f32 gear_ratio);
    // 0x71006698b0: sets / clears bit 2 of the current entry's flags (+0x10a8, indexed by +0x28)
    // under the CriticalSection. Placeholder name.
    void sub_71006698B0(bool on);

    // 0x7100669b48: sets bit 1 of the current entry of `_10b0` (indexed by `_2c`) and returns bit 1 of
    // the other entry. Placeholder name.
    bool sub_7100669B48();
    // 0x7100669b38 (declared only): `_10a4 |= 0x20` as a 32-bit read-modify-write (a byte `_10a4` gives a
    // byte one). Placeholder name.
    void sub_7100669B38();
    // 0x7100669af8: stores `value` in `_10c4` under mCS. Placeholder name.
    void sub_7100669AF8(f32 value);
    // 0x710066990c: sets / clears bit 0 of the current entry (`_28`) of `_10a8` and resets `_10d0` /
    // `_10d4` / `_10d8`. Placeholder name.
    void sub_710066990C(bool on);
    // 0x7100669a60: if `value >= 0` and the other entry of `_10a8` has bit 2 clear: lowers the current
    // entry of `_10b8` to `value` (true if it was lowered). Placeholder name.
    bool sub_7100669A60(f32 value);

    // 0x71006690b8: true if `proc` is linked in one of the 0x80 actor links (under mCS).
    bool sub_71006690B8(ksys::act::BaseProc* proc);
    // 0x7100668d44 (declared only): the per-frame update, run through the delegate `_10e0`.
    void sub_7100668D44();

    // Index (0 / 1) of the current entry of `_10a8`.
    s32 _28 = 0;
    // Index (0 / 1) of the current entry of `_10b0` (sub_7100669B48).
    s32 _2c = 0;
    struct Entry {
        // The constructor / destructor reset the entry (ctor: BaseProcLink(), reset(), stores).
        Entry() { reset(); }
        ~Entry() { reset(); }
        void reset() {
            mLink.reset();
            _10 = true;
            _18 = nullptr;
        }

        ksys::act::BaseProcLink mLink;
        // Whether the actor joined the system group (`join_system_group`).
        bool _10;
        void* _18;
    };
    Entry mEntries[0x80];
    // A second entry (0x1030; sub_710066956C / sub_71006695DC).
    Entry _1030;
    ksys::phys::SystemGroupHandler* _1050;
    sead::CriticalSection mCS;
    // Read as a rotation offset by DgnObj_DLC_DungeonRotateTag.
    f32 _1098;
    u32 _109c;
    u32 _10a0;
    // Bit 3 is tested by DgnObj_DLC_CWRotDirSwitch::calc_.
    u8 _10a4;
    u8 _10a5[3];
    // Two entries (current one: `_28`); bit 0 is read by DgnObj_DLC_CWRotDirSwitch::calc_ from the other
    // entry, bit 2 is set / cleared by sub_71006698B0.
    u32 _10a8[2];
    // Two entries (current one: `_2c`); bit 1 is set / read by sub_7100669B48.
    u32 _10b0[2];
    f32 _10b8[2];
    // Read by DgnObj_DLC_CogWheel_Physics_Ctr::sub_710035ED38 (> 0.6 enables its collision).
    f32 _10c0;
    f32 _10c4;
    // Least common multiple of the registered gear ratios (sub_7100669144).
    f32 _10c8;
    u32 _10cc;
    u32 _10d0 = 0;
    u32 _10d4 = 0;
    f32 _10d8 = 0;
    u8 _10dc;
    u8 _10dd;
    u8 _10de[0x10e0 - 0x10de];
    sead::Delegate<GearMgr> _10e0{this, &GearMgr::sub_7100668D44};
    f32 _1100 = 0.5f;
    u32 _1104 = 0;

private:
    // The initial / final state (inline in the original: the constructor and destructor store the same
    // values; name is a guess).
    void clear_();
};
KSYS_CHECK_SIZE_NX150(GearMgr, 0x1108);

}  // namespace uking
