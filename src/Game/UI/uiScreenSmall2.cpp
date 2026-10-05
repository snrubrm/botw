#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a41558
void ScreenRupee::sub_7100A41558() {
    _3610 = true;
    if (mState == 0 || mState == 3)
        sub_7100A410D8(1);
}

// 0x7100a20dd0
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
bool ScreenMainShortCut::sub_7100A20DD0() {
    if (mStateMachine.getState()->getId() == sUnk_71025ef170.getId())
        return false;
    return mStateMachine.getState()->getId() != sUnk_71025ef290.getId();
}

// 0x71009fd674
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
bool ScreenAppTool::sub_71009FD674() {
    return mStateMachine.getState()->getId() == sUnk_71025ec670.getId();
}

// 0x7100a31be0
void ScreenPauseMenuInfo::sub_7100A31BE0() {
    if (_3904 == 1)
        _3904 = 2;
    if (_391c == 1)
        _391c = 2;
}

// 0x7100a1e1e0
bool ScreenMainScreen::sub_7100A1E1E0() {
    if (!_3ca8)
        return false;
    return !_3ca8->isAnimOpenEnd(false);
}

}  // namespace uking::ui
