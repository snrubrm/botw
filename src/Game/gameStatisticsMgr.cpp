#include "Game/gameStatisticsMgr.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(StatisticsMgr)

}  // namespace uking

namespace uking {

u32 StatisticsMgr::sub_7100E33B10(f32* out, u32 count, void* stats, const sead::Vector3f* pos) {
    return sub_7100E33B14(this, out, count, stats, pos);
}

u32 StatisticsMgr::sub_7100E33EA0(u32* out, u32 count, void* stats, const sead::Vector3f* pos) {
    return sub_7100E33EA4(this, out, count, stats, pos);
}

s32 StatisticsMgr::query(f32* out, s32 count, void* stats, const sead::Vector3f* pos) {
    return sub_7100E34234(this, out, count, stats, pos);
}

}  // namespace uking
