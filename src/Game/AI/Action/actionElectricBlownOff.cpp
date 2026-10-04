#include "Game/AI/Action/actionElectricBlownOff.h"

namespace uking::action {

ElectricBlownOff::ElectricBlownOff(const InitArg& arg) : BlownOff(arg) {}

ElectricBlownOff::~ElectricBlownOff() = default;

bool ElectricBlownOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap) && sub_7100103E00(heap);
}

void ElectricBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void ElectricBlownOff::leave_() {
    BlownOff::leave_();
    if (!_1a8) {
        _1a8 = true;
        sub_710010451C();
    }
}

void ElectricBlownOff::loadParams_() {
    BlownOff::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricBlownOff::calc_() {
    BlownOff::calc_();
    if (_1a8)
        return;
    if (_19c.value <= sead::Mathf::epsilon()) {
        _1a8 = 1;
        sub_710010451C();
    } else {
        _19c.update();
    }
}

}  // namespace uking::action
