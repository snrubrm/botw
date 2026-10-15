#include "Game/Actor/Action/actionEventPlayUiOneTimeAnimAction.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiScreenNameTable.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

namespace {

// NON_MATCHING (static initializer 0x710011f87c): same stores, but our build places the header
// before the entries in .bss and schedules the first stores differently.
ui::ScreenNameTableHeader sScreenNameTableHeader;
ui::ScreenNameEntry sScreenNameEntries[] = {{"AppCamera", 4}};
// 0x71025b2188
sead::Buffer<ui::ScreenNameEntry> sScreenNames(sScreenNameEntries);

}  // namespace

EventPlayUiOneTimeAnimAction::EventPlayUiOneTimeAnimAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventPlayUiOneTimeAnimAction::~EventPlayUiOneTimeAnimAction() = default;

bool EventPlayUiOneTimeAnimAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiOneTimeAnimAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 99;
    _50 = nullptr;
    for (s32 i = 0; i < sScreenNames.size(); ++i) {
        if (mScreenName_d == sScreenNames[i].name) {
            _48 = sScreenNames[i].id;
            _50 = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(_48));
            if (!_50)
                break;
            if (*mClipIndex_d < 0)
                return;
            ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
            _50->m77(mAnimName_d);
            return;
        }
    }
    setFailed();
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
