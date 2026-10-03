#include "Game/AI/Action/actionEventControlRupeeUI.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventControlRupeeUI::EventControlRupeeUI(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventControlRupeeUI::~EventControlRupeeUI() = default;

bool EventControlRupeeUI::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventControlRupeeUI::oneShot_() {
    if (*mIsAppear_d)
        ui::sub_7100A9A0A4(*mTargetValue_d);
    else
        ui::sub_7100A9A160();
    return ksys::act::ai::Action::oneShot_();
}

void EventControlRupeeUI::loadParams_() {
    getDynamicParam(&mTargetValue_d, "TargetValue");
    getDynamicParam(&mIsAppear_d, "IsAppear");
}

}  // namespace uking::action
