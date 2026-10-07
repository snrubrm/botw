#include "Game/AI/Action/actionEventFade.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventFade::EventFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFade::~EventFade() = default;

bool EventFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: frame and color validation branches are arranged differently.
void EventFade::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = eui::ScreenMgr::instance();
    if (mgr) {
        auto* screen = sead::DynamicCast<ui::ScreenFadeDemo>(mgr->getScreen(ui::ScreenId::FadeDemo));
        if (screen) {
            if (*mFrame_d == 2)
                screen->sub_71010A01F8(2);
            else if (*mFrame_d == 1)
                screen->sub_71010A01F8(0);
            else if (*mFrame_d == 0)
                screen->sub_71010A01F8(1);
            else {
                setFailed();
                mFlags.set(Flag::Changeable);
                return;
            }

            if (*mColor_d == 1)
                screen->sub_71010A01A8(0);
            else if (*mColor_d == 0)
                screen->sub_71010A01A8(1);
            else {
                setFailed();
                mFlags.set(Flag::Changeable);
            }
            return;
        }
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

void EventFade::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventFade::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
    getDynamicParam(&mColor_d, "Color");
    getDynamicParam(&mDispMode_d, "DispMode");
}

void EventFade::calc_() {
    ksys::act::ai::Action::calc_();
}

ui::Screen* EventFade::sub_7100119888() {
    ui::ScreenFadeDemo* screen = nullptr;
    if (auto* mgr = eui::ScreenMgr::instance())
        screen = sead::DynamicCast<ui::ScreenFadeDemo>(mgr->getScreen(ui::ScreenId::FadeDemo));
    return screen;
}

}  // namespace uking::action
