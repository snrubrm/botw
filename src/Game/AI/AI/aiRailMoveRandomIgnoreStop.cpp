#include "Game/AI/AI/aiRailMoveRandomIgnoreStop.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

RailMoveRandomIgnoreStop::RailMoveRandomIgnoreStop(const InitArg& arg) : RailMoveWithClose(arg) {}

RailMoveRandomIgnoreStop::~RailMoveRandomIgnoreStop() = default;

bool RailMoveRandomIgnoreStop::init_(sead::Heap* heap) {
    return RailMoveWithClose::init_(heap);
}

void RailMoveRandomIgnoreStop::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveWithClose::enter_(params);
}

void RailMoveRandomIgnoreStop::calc_() {
    RailMoveWithClose::calc_();
}

void RailMoveRandomIgnoreStop::leave_() {
    RailMoveWithClose::leave_();
}

void RailMoveRandomIgnoreStop::loadParams_() {
    RailMoveWithClose::loadParams_();
    getStaticParam(&mStopRate_s, "StopRate");
}

void RailMoveRandomIgnoreStop::m39() {
    if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mStopRate_s)
        RailMove::m39();
    else
        sub_710032C088();
}

}  // namespace uking::ai
