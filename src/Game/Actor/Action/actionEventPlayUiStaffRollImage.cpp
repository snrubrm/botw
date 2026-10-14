#include "Game/Actor/Action/actionEventPlayUiStaffRollImage.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventPlayUiStaffRollImage::EventPlayUiStaffRollImage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventPlayUiStaffRollImage::~EventPlayUiStaffRollImage() = default;

bool EventPlayUiStaffRollImage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiStaffRollImage::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 start = mStartIdx_d ? *mStartIdx_d : 0;
    const s32 end = mEndIdx_d ? *mEndIdx_d : 0;
    if (start >= end) {
        setFailed();
        return;
    }
    auto* screen = sead::DynamicCast<ui::ScreenStaffRoll>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::StaffRoll));
    if (!screen) {
        setFailed();
        return;
    }
    if (*mClipIndex_d >= 0)
        screen->sub_7100A5E1C4(ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d),
                              start, end);
}

void EventPlayUiStaffRollImage::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiStaffRollImage::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mStartIdx_d, "StartIdx");
    getDynamicParam(&mEndIdx_d, "EndIdx");
}

void EventPlayUiStaffRollImage::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* screen = sead::DynamicCast<ui::ScreenStaffRoll>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::StaffRoll));
    if (!screen) {
        setFailed();
        return;
    }
    if (*mClipIndex_d >= 0) {
        screen->sub_7100A5E42C(
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f));
    } else {
        setFinished();
    }
}

}  // namespace uking::action
