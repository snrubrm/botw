#include "Game/AI/AI/aiDungeonRotateTagWaterChemical.h"

namespace uking::ai {

DungeonRotateTagWaterChemical::DungeonRotateTagWaterChemical(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DungeonRotateTagWaterChemical::~DungeonRotateTagWaterChemical() = default;

bool DungeonRotateTagWaterChemical::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagWaterChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = 0;
    _58 = 0xff;
    changeChild("待機");
}

void DungeonRotateTagWaterChemical::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagWaterChemical::loadParams_() {
    getStaticParam(&mSlowDownRotRadAccel_s, "SlowDownRotRadAccel");
    getStaticParam(&mSlowDownTimer_s, "SlowDownTimer");
    getStaticParam(&mRotRadAccel_s, "RotRadAccel");
    getStaticParam(&mReverseDotTh_s, "ReverseDotTh");
}

}  // namespace uking::ai
