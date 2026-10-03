#include "Game/AI/Action/actionEventDisappearCheckPointNum.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventDisappearCheckPointNum::EventDisappearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventDisappearCheckPointNum::~EventDisappearCheckPointNum() = default;

bool EventDisappearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventDisappearCheckPointNum::oneShot_() {
    ui::sub_7100A99D70();
    return ksys::act::ai::Action::oneShot_();
}

void EventDisappearCheckPointNum::loadParams_() {}

}  // namespace uking::action
