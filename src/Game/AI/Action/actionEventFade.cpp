#include "Game/AI/Action/actionEventFade.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventFade::EventFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFade::~EventFade() = default;

bool EventFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFade::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = eui::ScreenMgr::instance();
    if (mgr) {
        auto* screen = sead::DynamicCast<ui::ScreenFadeDemo>(mgr->getScreen(ui::ScreenId::FadeDemo));
        if (screen) {
            switch (*mFrame_d) {
            case 0:
                screen->sub_71010A01F8(1);
                break;
            case 1:
                screen->sub_71010A01F8(0);
                break;
            case 2:
                screen->sub_71010A01F8(2);
                break;
            default:
                setFailed();
                mFlags.set(Flag::Changeable);
                return;
            }

            switch (*mColor_d) {
            case 0:
                screen->sub_71010A01A8(1);
                break;
            case 1:
                screen->sub_71010A01A8(0);
                break;
            default:
                setFailed();
                mFlags.set(Flag::Changeable);
                break;
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
