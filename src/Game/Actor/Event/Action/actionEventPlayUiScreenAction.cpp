#include "Game/Actor/Event/Action/actionEventPlayUiScreenAction.h"
#include "Game/UI/uiScreenNameTable.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

namespace {

// 0x7102602c80; built by the static initializer 0x7100e464f0 (not decompiled).
ui::ScreenNameTableHeader sScreenNameTableHeader;
ui::ScreenNameEntry sScreenNameEntries[] = {
    {"GameTitle", 14}, {"GameOver", 48}, {"AppCamera", 4}, {"End", 72}, {"LastComplete", 80},
};
// 0x7102602c88
sead::Buffer<ui::ScreenNameEntry> sScreenNames(sScreenNameEntries);

}  // namespace

EventPlayUiScreenAction::EventPlayUiScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiScreenAction::~EventPlayUiScreenAction() = default;

bool EventPlayUiScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiScreenAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 99;
    _40 = nullptr;
    for (s32 i = 0; i < sScreenNames.size(); ++i) {
        if (mScreenName_d == sScreenNames[i].name) {
            _38 = sScreenNames[i].id;
            ksys::ui::sub_7100EDC530(_38, nullptr);
            const s32 index = _38;
            _40 = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(index));
            if (!_40)
                break;
            if (*mClipIndex_d < 0) {
                _40->open(1);
                return;
            }
            const f32 frame = ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
            _40->m73(frame);
            return;
        }
    }
    setFailed();
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
