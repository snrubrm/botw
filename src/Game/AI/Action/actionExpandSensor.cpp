#include "Game/AI/Action/actionExpandSensor.h"

namespace uking::action {

ExpandSensor::ExpandSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensor::~ExpandSensor() = default;

bool ExpandSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExpandSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExpandSensor::leave_() {
    sub_710012A680();
}

void ExpandSensor::loadParams_() {
    getStaticParam(&mParams.mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mParams.mAtkType_s, "AtkType");
    getStaticParam(&mParams.mOffLength_s, "OffLength");
    getStaticParam(&mParams.mOnLength_s, "OnLength");
}

void ExpandSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
