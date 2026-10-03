#include "Game/AI/Action/actionShiekSensorPlusDownloadDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

ShiekSensorPlusDownloadDemo::ShiekSensorPlusDownloadDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ShiekSensorPlusDownloadDemo::~ShiekSensorPlusDownloadDemo() = default;

bool ShiekSensorPlusDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShiekSensorPlusDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = 0;
}

void ShiekSensorPlusDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShiekSensorPlusDownloadDemo::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void ShiekSensorPlusDownloadDemo::calc_() {
    if (_28 == 1) {
        if (ui::sub_7100A9A938(false))
            setFinished();
    }
    if (_28 == 0) {
        ui::sub_7100A9F27C(*mIsPlayerClose_d);
        _28 = _28 + 1;
    }
}

}  // namespace uking::action
