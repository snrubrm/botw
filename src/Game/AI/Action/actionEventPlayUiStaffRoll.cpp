#include "Game/AI/Action/actionEventPlayUiStaffRoll.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventPlayUiStaffRoll::EventPlayUiStaffRoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiStaffRoll::~EventPlayUiStaffRoll() = default;

bool EventPlayUiStaffRoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiStaffRoll::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiStaffRoll::leave_() {
    if (*mClipIndex_d < 0)
        return;
    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::StaffRoll));
    if (screen)
        screen->m76();
}

void EventPlayUiStaffRoll::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mStartIdx_d, "StartIdx");
}

void EventPlayUiStaffRoll::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
