#include "Game/AI/Action/actionEventTalkEndAction.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

EventTalkEndAction::EventTalkEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventTalkEndAction::~EventTalkEndAction() = default;

bool EventTalkEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventTalkEndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void EventTalkEndAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventTalkEndAction::loadParams_() {}

void EventTalkEndAction::calc_() {
    auto* ui = ui::UI::instance();
    if (isFinished() || isFailed())
        return;
    if (!ui->sub_71010A5888()) {
        setFinished();
        return;
    }
    if (!_1c) {
        _1c = true;
        ui->sub_71010A6B98(nullptr);
    }
}

}  // namespace uking::action
