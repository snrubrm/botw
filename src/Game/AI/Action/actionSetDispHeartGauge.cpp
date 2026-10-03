#include "Game/AI/Action/actionSetDispHeartGauge.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

SetDispHeartGauge::SetDispHeartGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispHeartGauge::~SetDispHeartGauge() = default;

bool SetDispHeartGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetDispHeartGauge::oneShot_() {
    ui::sub_7100A94B40(*mIsDisplay_d, *mIsDisplayEx_d, *mIsGetDemo_d);
    return ksys::act::ai::Action::oneShot_();
}

void SetDispHeartGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
    getDynamicParam(&mIsGetDemo_d, "IsGetDemo");
}

}  // namespace uking::action
