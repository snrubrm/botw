#include "Game/AI/Action/actionEventChangeFadeColor.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventChangeFadeColor::EventChangeFadeColor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventChangeFadeColor::~EventChangeFadeColor() = default;

bool EventChangeFadeColor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventChangeFadeColor::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* screen = sead::DynamicCast<ui::Fade>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade))) {
        if (*mColor_d)
            setFailed();
        else
            screen->x(true);
    }
}

void EventChangeFadeColor::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventChangeFadeColor::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
    getDynamicParam(&mColor_d, "Color");
}

void EventChangeFadeColor::calc_() {
    if (isFinished() || isFailed())
        return;
}

}  // namespace uking::action
