#include "Game/AI/Action/actionEventFade.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

EventFade::EventFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFade::~EventFade() = default;

bool EventFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFade::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
