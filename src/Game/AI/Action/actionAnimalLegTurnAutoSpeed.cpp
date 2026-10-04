#include "Game/AI/Action/actionAnimalLegTurnAutoSpeed.h"

namespace uking::action {

AnimalLegTurnAutoSpeed::AnimalLegTurnAutoSpeed(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalLegTurnAutoSpeed::~AnimalLegTurnAutoSpeed() = default;

bool AnimalLegTurnAutoSpeed::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalLegTurnAutoSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = 0.6f;
    _6c = 0.6f;
    _70 = 0.0f;
    _1b4 = false;
    _1c4 = 0.0f;
    sub_710008FAC0();
    ForkAnimalASPlay::enter_(params);
}

void AnimalLegTurnAutoSpeed::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalLegTurnAutoSpeed::loadParams_() {
    ForkAnimalASPlay::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalLegTurnAutoSpeed::calc_() {
    ForkAnimalASPlay::calc_();
}

}  // namespace uking::action
