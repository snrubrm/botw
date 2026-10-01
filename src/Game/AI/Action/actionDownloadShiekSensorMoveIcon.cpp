#include "Game/AI/Action/actionDownloadShiekSensorMoveIcon.h"

namespace uking::action {

DownloadShiekSensorMoveIcon::DownloadShiekSensorMoveIcon(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DownloadShiekSensorMoveIcon::~DownloadShiekSensorMoveIcon() = default;

bool DownloadShiekSensorMoveIcon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadShiekSensorMoveIcon::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
}

void DownloadShiekSensorMoveIcon::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadShiekSensorMoveIcon::loadParams_() {}

void DownloadShiekSensorMoveIcon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
