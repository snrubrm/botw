#include "Game/AI/Action/actionAnimalFreeze.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

AnimalFreeze::AnimalFreeze(const InitArg& arg) : HorseFreeze(arg) {}

AnimalFreeze::~AnimalFreeze() = default;

bool AnimalFreeze::init_(sead::Heap* heap) {
    return HorseFreeze::init_(heap);
}

void AnimalFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFreeze::enter_(params);
}

void AnimalFreeze::leave_() {
    HorseFreeze::leave_();
    sub_71005DB434(mActor);
}

void AnimalFreeze::loadParams_() {
    HorseFreeze::loadParams_();
}

void AnimalFreeze::calc_() {
    HorseFreeze::calc_();
}

}  // namespace uking::action
