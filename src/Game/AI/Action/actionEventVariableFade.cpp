#include "Game/AI/Action/actionEventVariableFade.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventVariableFade::EventVariableFade(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventVariableFade::~EventVariableFade() = default;

bool EventVariableFade::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the color validation branches have a different block order.
void EventVariableFade::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::evt::Manager::instance()) {
        if (auto* mgr = eui::ScreenMgr::instance()) {
            if (auto* screen = sead::DynamicCast<ui::ScreenFadeDemo>(mgr->getScreen(ui::ScreenId::FadeDemo))) {
                if (*mColor_d == 1) {
                    screen->sub_71010A01A8(0);
                } else if (*mColor_d == 0) {
                    screen->sub_71010A01A8(1);
                } else {
                    setFailed();
                    mFlags.set(Flag::Changeable);
                    return;
                }
                f32 fade_time = *mFadeTime_d;
                if (fade_time > *mDuration_d)
                    fade_time = *mDuration_d;
                screen->m73(fade_time);
                return;
            }
        }
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

void EventVariableFade::leave_() {
    ksys::evt::Manager::instance()->sub_7100DB1158(*mClipIndex_d);
    if (ksys::evt::Manager::instance()) {
        if (auto* screen = sub_7100127B30())
            screen->m76();
    }
}

void EventVariableFade::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mColor_d, "Color");
    getDynamicParam(&mDuration_d, "Duration");
    getDynamicParam(&mFadeTime_d, "FadeTime");
}

void EventVariableFade::calc_() {
    auto* manager = ksys::evt::Manager::instance();
    if (manager && sub_7100127B30()) {
        const int idx = *mClipIndex_d;
        if (idx >= 0)
            manager->sub_7100DB1138(idx);
    } else {
        setFailed();
        mFlags.set(Flag::Changeable);
    }
}

ui::ScreenFadeDemo* EventVariableFade::sub_7100127B30() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return nullptr;
    return sead::DynamicCast<ui::ScreenFadeDemo>(mgr->getScreen(ui::ScreenId::FadeDemo));
}

}  // namespace uking::action
