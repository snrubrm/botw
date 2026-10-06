#include "Game/AI/Action/actionEventPlayUiScreenAction.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventPlayUiScreenAction::EventPlayUiScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiScreenAction::~EventPlayUiScreenAction() = default;

bool EventPlayUiScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiScreenAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiScreenAction::leave_() {
    const s32 index = _38;
    auto* screen = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(index));
    if (screen != _40) {
        setFailed();
        return;
    }
    if (_40)
        _40->m76();
}

void EventPlayUiScreenAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mScreenName_d, "ScreenName");
}

void EventPlayUiScreenAction::calc_() {
    if (isFinished() || isFailed())
        return;

    const s32 index = _38;
    auto* screen = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(index));
    if (screen != _40) {
        setFailed();
        return;
    }

    if (*mClipIndex_d >= 0) {
        const f32 progress =
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f);
        _40->m74(progress);
    } else if (_40->isOpened()) {
        setFinished();
    }
}

}  // namespace uking::action
