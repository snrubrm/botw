#include "Game/AI/Action/actionDownloadShiekSensor.h"

namespace uking::action {

DownloadShiekSensor::DownloadShiekSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadShiekSensor::~DownloadShiekSensor() = default;

bool DownloadShiekSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadShiekSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
}

void DownloadShiekSensor::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadShiekSensor::loadParams_() {}

void DownloadShiekSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
