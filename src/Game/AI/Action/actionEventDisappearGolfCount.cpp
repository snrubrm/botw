#include "Game/AI/Action/actionEventDisappearGolfCount.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventDisappearGolfCount::EventDisappearGolfCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDisappearGolfCount::~EventDisappearGolfCount() = default;

bool EventDisappearGolfCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventDisappearGolfCount::oneShot_() {
    ui::sub_7100A99860();
    return ksys::act::ai::Action::oneShot_();
}

void EventDisappearGolfCount::loadParams_() {}

}  // namespace uking::action
