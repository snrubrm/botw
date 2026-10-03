#include "Game/AI/Action/actionEventDisappearRaceResult.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventDisappearRaceResult::EventDisappearRaceResult(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearRaceResult::~EventDisappearRaceResult() = default;

bool EventDisappearRaceResult::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventDisappearRaceResult::oneShot_() {
    ui::sub_7100A99FE8();
    return ksys::act::ai::Action::oneShot_();
}

void EventDisappearRaceResult::loadParams_() {}

}  // namespace uking::action
