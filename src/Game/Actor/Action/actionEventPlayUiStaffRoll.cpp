#include "Game/Actor/Action/actionEventPlayUiStaffRoll.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventPlayUiStaffRoll::EventPlayUiStaffRoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiStaffRoll::~EventPlayUiStaffRoll() = default;

bool EventPlayUiStaffRoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the range block differs only in register allocation (the start/end pair and _8 are rotated
// through w9/w11) and in where the compiler places the shared _8 = true.
void EventPlayUiStaffRoll::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 start = mStartIdx_d ? *mStartIdx_d : 0;
    switch (start) {
    case 1:
        ui::sUnk_71025f5450._0 = 0;
        ui::sUnk_71025f5450._4 = 1000;
        ui::sUnk_71025f5450._8 = true;
        ui::sUnk_71025f5450._9 = false;
        break;
    case 2:
        ui::sUnk_71025f5450._0 = 1001;
        ui::sUnk_71025f5450._4 = 9999;
        ui::sUnk_71025f5450._8 = false;
        ui::sUnk_71025f5450._9 = true;
        break;
    default:
        ui::sUnk_71025f5450._0 = 0;
        ui::sUnk_71025f5450._4 = 9999;
        ui::sUnk_71025f5450._8 = true;
        ui::sUnk_71025f5450._9 = true;
        break;
    }

    ksys::ui::sub_7100EDC530(ui::ScreenId::StaffRoll, nullptr);

    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::StaffRoll));
    if (!screen) {
        setFailed();
        return;
    }

    if (*mClipIndex_d < 0) {
        screen->open(1);
        return;
    }

    const f32 progress = ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
    screen->m73(progress);
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
