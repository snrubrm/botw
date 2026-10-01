#include "Game/AI/AI/aiInWaterKeepSelect.h"

namespace uking::ai {

InWaterKeepSelect::InWaterKeepSelect(const InitArg& arg) : InWaterSelect(arg) {}

InWaterKeepSelect::~InWaterKeepSelect() = default;

bool InWaterKeepSelect::init_(sead::Heap* heap) {
    return InWaterSelect::init_(heap);
}

void InWaterKeepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    InWaterSelect::enter_(params);
}

void InWaterKeepSelect::calc_() {
    InWaterSelect::calc_();
}

void InWaterKeepSelect::leave_() {
    *mIsKeepInWater_a = isCurrentChild("水中");
    InWaterSelect::leave_();
}

void InWaterKeepSelect::loadParams_() {
    InWaterSelect::loadParams_();
    getAITreeVariable(&mIsKeepInWater_a, "IsKeepInWater");
}

}  // namespace uking::ai
