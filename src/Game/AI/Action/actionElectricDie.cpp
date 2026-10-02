#include "Game/AI/Action/actionElectricDie.h"
#include "Game/AI/aiUnk_710072BA90.h"

namespace uking::action {

ElectricDie::ElectricDie(const InitArg& arg) : ElectricBlownOff(arg) {}

ElectricDie::~ElectricDie() = default;

void ElectricDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ElectricBlownOff::enter_(params);
    sub_710072BB28(mActor);
}

void ElectricDie::leave_() {
    ElectricBlownOff::leave_();
}

void ElectricDie::loadParams_() {
    ElectricBlownOff::loadParams_();
}

}  // namespace uking::action
