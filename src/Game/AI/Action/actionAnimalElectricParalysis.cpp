#include "Game/AI/Action/actionAnimalElectricParalysis.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

AnimalElectricParalysis::AnimalElectricParalysis(const InitArg& arg)
    : HorseElectricParalysis(arg) {}

AnimalElectricParalysis::~AnimalElectricParalysis() = default;

bool AnimalElectricParalysis::init_(sead::Heap* heap) {
    return HorseElectricParalysis::init_(heap);
}

void AnimalElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseElectricParalysis::enter_(params);
}

void AnimalElectricParalysis::leave_() {
    HorseElectricParalysis::leave_();
    sub_71005DB434(mActor);
}

void AnimalElectricParalysis::loadParams_() {
    HorseElectricParalysis::loadParams_();
}

void AnimalElectricParalysis::calc_() {
    HorseElectricParalysis::calc_();
}

}  // namespace uking::action
