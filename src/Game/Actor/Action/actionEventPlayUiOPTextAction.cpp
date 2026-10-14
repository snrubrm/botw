#include "Game/Actor/Action/actionEventPlayUiOPTextAction.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventPlayUiOPTextAction::EventPlayUiOPTextAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiOPTextAction::~EventPlayUiOPTextAction() = default;

bool EventPlayUiOPTextAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOPTextAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::ui::sub_7100EDC530(81, nullptr);
    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::OPtext));
    if (!screen) {
        _30 = nullptr;
        setFailed();
        return;
    }

    _30 = screen;
    if (*mClipIndex_d < 0) {
        screen->open(1);
        return;
    }

    const f32 progress = ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
    if (auto* text = sead::DynamicCast<ui::ScreenOPtext>(_30))
        text->m154(*mTextType_d);
    _30->m73(progress);
}

void EventPlayUiOPTextAction::leave_() {
    _30->m76();
}

void EventPlayUiOPTextAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mTextType_d, "TextType");
}

void EventPlayUiOPTextAction::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* screen = sead::DynamicCast<ui::Screen>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::OPtext));
    if (screen != _30) {
        if (!(ksys::evt::Manager::instance()->_1d2f4_bytes[1] & 8))
            setFailed();
        return;
    }

    if (*mClipIndex_d >= 0) {
        const f32 progress =
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f);
        _30->m74(progress);
    } else if (_30->isOpened()) {
        setFinished();
    }
}

}  // namespace uking::action
