#include "Game/AI/Action/actionSetDispStaminaGauge.h"

// Source owners and namespaces are unknown.
void sub_71009452A4(bool display);
void sub_71009452B4(bool display);

namespace uking::action {

SetDispStaminaGauge::SetDispStaminaGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispStaminaGauge::~SetDispStaminaGauge() = default;

bool SetDispStaminaGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetDispStaminaGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
}

bool SetDispStaminaGauge::oneShot_() {
    sub_71009452A4(mIsDisplay_d && *mIsDisplay_d);
    sub_71009452B4(mIsDisplayEx_d && *mIsDisplayEx_d);
    return true;
}

}  // namespace uking::action
