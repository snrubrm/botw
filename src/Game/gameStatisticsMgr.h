#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace uking {

// Placeholder declaration (names from the CSV: StatisticsMgr::createInstance 0x7100e31d1c, init
// 0x7100e32138, getStatsPointer 0x7100e33960, query 0x7100e34230 ...; the instance pointer is at
// 0x71026026c8; the namespace is a guess). Only what the AI classes use is declared.
// TODO: incomplete.
class StatisticsMgr {
    SEAD_SINGLETON_DISPOSER(StatisticsMgr)
    StatisticsMgr();
    ~StatisticsMgr();

public:
    // 0x7100e32a18 (declaration only): stores the horizontal position and the derived map-cell
    // coordinates of `pos`.
    void updatePosition(const sead::Vector3f* pos);
    // 0x7100e33960 (declaration only): binary search of the stats table by name ("water_depth",
    // "water_distance", ...); null if there is none.
    void* getStatsPointer(const sead::SafeString& name);
    // 0x7100e34230 (declaration only; a thunk to 0x7100e34234): looks `count` values of the stats
    // `stats` up at `pos` (only x / z select the map cell) into `out`. Placeholder signature.
    s32 query(f32* out, s32 count, void* stats, const sead::Vector3f* pos);
    // E33B10 is the float statistics query thunk; the native result is a value count.
    u32 sub_7100E33B10(f32* out, u32 count, void* stats, const sead::Vector3f* pos);
    // Full E33EA0/E33EA4 and independent 12CB14C query 32-bit values and return the count.
    u32 sub_7100E33EA0(u32* out, u32 count, void* stats, const sead::Vector3f* pos);

    // Bits 1 / 2 gate the WolfLink "player_safety_restart" statistics lookup.
    /* 0x020 */ u8 _0[0x110 - 0x20];
    /* 0x110 */ u32 _110 = 0;
};

// The implementations the three public query methods forward to (0x7100e33b14 / 0x7100e33ea4 /
// 0x7100e34234). They take the manager as the first argument and remain undecompiled.
u32 sub_7100E33B14(StatisticsMgr* mgr, f32* out, u32 count, void* stats,
                   const sead::Vector3f* pos);
u32 sub_7100E33EA4(StatisticsMgr* mgr, u32* out, u32 count, void* stats,
                   const sead::Vector3f* pos);
s32 sub_7100E34234(StatisticsMgr* mgr, f32* out, s32 count, void* stats,
                   const sead::Vector3f* pos);

}  // namespace uking
