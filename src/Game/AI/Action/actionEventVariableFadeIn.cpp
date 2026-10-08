#include "Game/AI/Action/actionEventVariableFadeIn.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventVariableFadeIn::EventVariableFadeIn(const InitArg& arg) : EventVariableFade(arg) {}

EventVariableFadeIn::~EventVariableFadeIn() = default;

bool EventVariableFadeIn::init_(sead::Heap* heap) {
    return EventVariableFade::init_(heap);
}

// NON_MATCHING: the two color switches compile as cbz-first (==0 tested before ==1);
// the original tests ==1 first (cmp #1 + b.eq, then cbnz to the failed path).
void EventVariableFadeIn::enter_(ksys::act::ai::InlineParamPack* /*params*/) {
    f32 fade_time = *mFadeTime_d > *mDuration_d ? *mDuration_d : *mFadeTime_d;
    auto* demo = sub_7100127B30();
    auto* fade = sead::DynamicCast<ui::Fade>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    if (demo->isOpened() || demo->isOpening()) {
        demo->sub_71010A01F8(3);
        demo->_354 = 0;
        if (*mColor_d == 1) {
            demo->sub_71010A01A8(0);
        } else if (*mColor_d == 0) {
            demo->sub_71010A01A8(1);
        } else {
            setFailed();
            mFlags.set(Flag::Changeable);
            return;
        }
        demo->m73(fade_time);
        _40 = false;
    } else {
        fade->x_1(3);
        fade->_a20 = 0;
        if (*mColor_d == 1) {
            fade->stopColorAnimatorAt(0);
        } else if (*mColor_d == 0) {
            fade->stopColorAnimatorAt(1);
        } else {
            setFailed();
            mFlags.set(Flag::Changeable);
            return;
        }
        fade->m73(fade_time);
        _40 = true;
    }
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
