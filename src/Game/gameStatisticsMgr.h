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
    // 0x7100e33960 (declaration only): binary search of the stats table by name ("water_depth",
    // "water_distance", ...); null if there is none.
    void* getStatsPointer(const sead::SafeString& name);
    // 0x7100e34230 (declaration only; a thunk to 0x7100e34234): looks `count` values of the stats
    // `stats` up at `pos` (only x / z select the map cell) into `out`. Placeholder signature.
    s32 query(f32* out, s32 count, void* stats, const sead::Vector3f* pos);
};

}  // namespace uking
