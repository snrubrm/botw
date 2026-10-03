#include "Game/AI/Action/actionDownloadShiekSensorMoveIcon.h"
#include "Game/UI/uiUtils.h"

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
    if (_1c == 1) {
        if (ui::sub_7100A9A938(true))
            setFinished();
    }
    if (_1c == 0) {
        ui::sub_7100A9F358();
        _1c = _1c + 1;
    }
}

}  // namespace uking::action
