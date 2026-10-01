#include "Game/AI/AI/aiLynelDistanceLostCheck.h"

namespace uking::ai {

LynelDistanceLostCheck::LynelDistanceLostCheck(const InitArg& arg) : DistanceLostCheck(arg) {}

LynelDistanceLostCheck::~LynelDistanceLostCheck() = default;

bool LynelDistanceLostCheck::init_(sead::Heap* heap) {
    return DistanceLostCheck::init_(heap);
}

void LynelDistanceLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    DistanceLostCheck::enter_(params);
}

void LynelDistanceLostCheck::calc_() {
    DistanceLostCheck::calc_();
}

void LynelDistanceLostCheck::leave_() {
    DistanceLostCheck::leave_();
}

void LynelDistanceLostCheck::loadParams_() {
    DistanceLostCheck::loadParams_();
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

bool LynelDistanceLostCheck::m34() {
    return DistanceLostCheck::m34() && !(*mLynelAIFlags_a & 0x10);
}

}  // namespace uking::ai
