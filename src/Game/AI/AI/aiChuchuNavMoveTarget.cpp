#include "Game/AI/AI/aiChuchuNavMoveTarget.h"

namespace uking::ai {

ChuchuNavMoveTarget::ChuchuNavMoveTarget(const InitArg& arg) : NavMoveTarget(arg) {}

ChuchuNavMoveTarget::~ChuchuNavMoveTarget() = default;

bool ChuchuNavMoveTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void ChuchuNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
    const f32 half_time = *mWallHitTime_s * 0.5f;
    if (half_time > 0)
        _388._84 = half_time;
    if (*mWallHitTime_s > 0)
        _388._88 = *mWallHitTime_s;
    _388._78 = _388._88;
    _388._7c = 0;
    _388._80 = 0;
    _388._90.setUndef();
    _388._8c = false;
}

void ChuchuNavMoveTarget::leave_() {
    NavMoveTarget::leave_();
}

void ChuchuNavMoveTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mWallHitTime_s, "WallHitTime");
}

}  // namespace uking::ai
