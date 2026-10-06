#include "Game/AI/Action/actionEventPlayUiStaffRoll.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

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
    if (isFinished() || isFailed())
        return;

    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::StaffRoll));
    if (!screen) {
        setFailed();
        return;
    }

    if (*mClipIndex_d >= 0) {
        const f32 progress =
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f);
        screen->m74(progress);
    } else if (screen->isOpened()) {
        setFinished();
    }
}

}  // namespace uking::action
