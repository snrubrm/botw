#include "Game/AI/Action/actionDownloadShiekSensor.h"
#include "Game/UI/uiUtils.h"

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
    if (_1c == 1) {
        if (ui::sub_7100A9A938(false))
            setFinished();
    }
    if (_1c == 0) {
        ui::sub_7100A9F138();
        _1c = _1c + 1;
    }
}

}  // namespace uking::action
