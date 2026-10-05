#include "Game/AI/Action/actionEventCloseMessageTipsAction.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

EventCloseMessageTipsAction::EventCloseMessageTipsAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCloseMessageTipsAction::~EventCloseMessageTipsAction() = default;

bool EventCloseMessageTipsAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCloseMessageTipsAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* manager = ui::UI::instance()) {
        manager->closeMessageTipsScreen();
        setFinished();
    } else {
        setFailed();
    }
    mFlags.set(Flag::Changeable);
}

void EventCloseMessageTipsAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCloseMessageTipsAction::loadParams_() {}

void EventCloseMessageTipsAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
