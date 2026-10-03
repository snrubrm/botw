#include "Game/AI/Action/actionWaterUpDownDrivenPreAttack.h"

namespace uking::action {

WaterUpDownDrivenPreAttack::WaterUpDownDrivenPreAttack(const InitArg& arg)
    : WaterUpDownAnmDrivenMove(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WaterUpDownDrivenPreAttack::~WaterUpDownDrivenPreAttack() {
    ;
}

bool WaterUpDownDrivenPreAttack::init_(sead::Heap* heap) {
    return WaterUpDownAnmDrivenMove::init_(heap);
}

void WaterUpDownDrivenPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterUpDownAnmDrivenMove::enter_(params);
}

void WaterUpDownDrivenPreAttack::leave_() {
    WaterUpDownAnmDrivenMove::leave_();
}

void WaterUpDownDrivenPreAttack::loadParams_() {
    WaterUpDownAnmDrivenMove::loadParams_();
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WaterUpDownDrivenPreAttack::calc_() {
    WaterUpDownAnmDrivenMove::calc_();
}

}  // namespace uking::action
