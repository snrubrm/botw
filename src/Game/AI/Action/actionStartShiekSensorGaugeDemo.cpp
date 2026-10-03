#include "Game/AI/Action/actionStartShiekSensorGaugeDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

StartShiekSensorGaugeDemo::StartShiekSensorGaugeDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

StartShiekSensorGaugeDemo::~StartShiekSensorGaugeDemo() = default;

bool StartShiekSensorGaugeDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartShiekSensorGaugeDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = 0;
}

void StartShiekSensorGaugeDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartShiekSensorGaugeDemo::loadParams_() {
    getDynamicParam(&mReactionNum_d, "ReactionNum");
}

void StartShiekSensorGaugeDemo::calc_() {
    if (_28 == 1) {
        if (!ui::sub_7100A9F458())
            setFinished();
    }
    if (_28 == 0) {
        ui::sub_7100A9F410(*mReactionNum_d);
        _28 = _28 + 1;
    }
}

}  // namespace uking::action
