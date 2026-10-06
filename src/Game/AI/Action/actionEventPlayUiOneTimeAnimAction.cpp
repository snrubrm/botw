#include "Game/AI/Action/actionEventPlayUiOneTimeAnimAction.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventPlayUiOneTimeAnimAction::EventPlayUiOneTimeAnimAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventPlayUiOneTimeAnimAction::~EventPlayUiOneTimeAnimAction() = default;

bool EventPlayUiOneTimeAnimAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOneTimeAnimAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiOneTimeAnimAction::leave_() {
    auto* screen = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(_48));
    if (screen != _50) {
        setFailed();
        return;
    }
    if (_50)
        _50->m79();
}

void EventPlayUiOneTimeAnimAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mScreenName_d, "ScreenName");
    getDynamicParam(&mAnimName_d, "AnimName");
}

void EventPlayUiOneTimeAnimAction::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* screen = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(_48));
    if (screen != _50) {
        setFailed();
        return;
    }

    if (*mClipIndex_d >= 0) {
        const f32 frame =
            sead::Mathf::clampMin(ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d), 0.0f);
        _50->m78(frame);
    }
}

}  // namespace uking::action
