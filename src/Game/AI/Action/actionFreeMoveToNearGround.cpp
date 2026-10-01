#include "Game/AI/Action/actionFreeMoveToNearGround.h"

namespace uking::action {

FreeMoveToNearGround::FreeMoveToNearGround(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToNearGround::~FreeMoveToNearGround() = default;

bool FreeMoveToNearGround::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

// NON_MATCHING: the original does not merge the Timer and VFRValue constant stores into 64-bit pairs
void FreeMoveToNearGround::enter_(ksys::act::ai::InlineParamPack* params) {
    _f8 = 0;
    FreeMoveToTarget::enter_(params);
    _e0 = ksys::Timer(45.0f, 45.0f);
    _ec.value = 1.0f;
    _ec.prev_value = 1.0f;
}

void FreeMoveToNearGround::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToNearGround::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mReduceSpeedRateWithWind_s, "ReduceSpeedRateWithWind");
    getStaticParam(&mWindVelocityLimit4Reduce_s, "WindVelocityLimit4Reduce");
}

void FreeMoveToNearGround::calc_() {
    FreeMoveToTarget::calc_();
}

f32 FreeMoveToNearGround::m36() {
    return _f8;
}

}  // namespace uking::action
