#include "Game/AI/Action/actionEventFadeIn.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventFadeIn::EventFadeIn(const InitArg& arg) : EventFade(arg) {}

EventFadeIn::~EventFadeIn() = default;

bool EventFadeIn::init_(sead::Heap* heap) {
    return EventFade::init_(heap);
}

void EventFadeIn::enter_(ksys::act::ai::InlineParamPack* params) {
    EventFade::enter_(params);
}

void EventFadeIn::leave_() {}

void EventFadeIn::loadParams_() {
    EventFade::loadParams_();
}

void EventFadeIn::calc_() {
    if (isFinished() || isFailed())
        return;

    ui::Screen* screen;
    if (_40)
        screen = sead::DynamicCast<ui::Fade>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    else
        screen = sub_7100119888();

    if (screen->isClosed()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    } else if (!screen->isClosedOrClosing()) {
        setFailed();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
