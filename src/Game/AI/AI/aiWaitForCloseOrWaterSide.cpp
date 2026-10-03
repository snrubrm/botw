#include "Game/AI/AI/aiWaitForCloseOrWaterSide.h"
#include <limits>
#include "Game/gameStatisticsMgr.h"

namespace uking::ai {

WaitForCloseOrWaterSide::WaitForCloseOrWaterSide(const InitArg& arg) : WaitForTargetClose(arg) {}

WaitForCloseOrWaterSide::~WaitForCloseOrWaterSide() = default;

bool WaitForCloseOrWaterSide::init_(sead::Heap* heap) {
    if (!WaitForTargetClose::init_(heap))
        return false;
    _60 = StatisticsMgr::instance()->getStatsPointer("water_distance");
    return true;
}

void WaitForCloseOrWaterSide::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitForTargetClose::enter_(params);
}

void WaitForCloseOrWaterSide::calc_() {
    WaitForTargetClose::calc_();
}

void WaitForCloseOrWaterSide::leave_() {
    WaitForTargetClose::leave_();
}

bool WaitForCloseOrWaterSide::m34(f32 distance) {
    if (WaitForTargetClose::m34(distance))
        return true;
    auto* mgr = StatisticsMgr::instance();
    if (!mgr)
        return false;
    f32 water_distance = std::numeric_limits<f32>::infinity();
    if (!mgr->query(&water_distance, 1, _60, mTargetPos_d))
        return false;
    water_distance *= 200.0f;
    return water_distance <= *mDistFromWater_s;
}

void WaitForCloseOrWaterSide::loadParams_() {
    WaitForTargetClose::loadParams_();
    getStaticParam(&mDistFromWater_s, "DistFromWater");
}

}  // namespace uking::ai
