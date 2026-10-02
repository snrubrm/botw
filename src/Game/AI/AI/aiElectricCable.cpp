#include "Game/AI/AI/aiElectricCable.h"

namespace uking::ai {

// NON_MATCHING: zero stores to 0x38-0x50 are paired differently (stp 0x40/0x48 scheduled last)
ElectricCable::ElectricCable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ElectricCable::~ElectricCable() = default;

bool ElectricCable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ElectricCable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ElectricCable::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ElectricCable::loadParams_() {
    getMapUnitParam(&mIsDisplayOnUI_m, "IsDisplayOnUI");
}

}  // namespace uking::ai
