#include "Game/AI/Action/actionEventPlayUiOPTextAction.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventPlayUiOPTextAction::EventPlayUiOPTextAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiOPTextAction::~EventPlayUiOPTextAction() = default;

bool EventPlayUiOPTextAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOPTextAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
