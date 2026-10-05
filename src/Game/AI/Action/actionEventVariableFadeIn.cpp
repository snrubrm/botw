#include "Game/AI/Action/actionEventVariableFadeIn.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventVariableFadeIn::EventVariableFadeIn(const InitArg& arg) : EventVariableFade(arg) {}

EventVariableFadeIn::~EventVariableFadeIn() = default;

bool EventVariableFadeIn::init_(sead::Heap* heap) {
    return EventVariableFade::init_(heap);
}

void EventVariableFadeIn::enter_(ksys::act::ai::InlineParamPack* params) {
    EventVariableFade::enter_(params);
}

void EventVariableFadeIn::leave_() {
    if (*mClipIndex_d < 0)
        return;
    ksys::evt::Manager::instance()->sub_7100DB1158(*mClipIndex_d);
    ui::Screen* screen;
    if (_40)
        screen = sead::DynamicCast<ui::Fade>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    else
        screen = sub_7100127B30();
    screen->m76();
    screen->close(-4);
}

void EventVariableFadeIn::loadParams_() {
    EventVariableFade::loadParams_();
}

void EventVariableFadeIn::calc_() {
    if (*mClipIndex_d < 0)
        return;
    const f32 frame = ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d);
    ui::Screen* screen;
    if (_40)
        screen = sead::DynamicCast<ui::Fade>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    else
        screen = sub_7100127B30();
    if (frame >= 0.0f)
        screen->m74(frame);
}

}  // namespace uking::action
