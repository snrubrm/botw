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

// 0x7100a1ab58
void ScreenMainScreen::sub_7100A1AB58(s32 a1) {
    if (_3658)
        _3658->_150 = a1;
}

// 0x7100a1e1e0
bool ScreenMainScreen::sub_7100A1E1E0() {
    if (!_3ca8)
        return false;
    return !_3ca8->isAnimOpenEnd(false);
}

}  // namespace uking::ui

namespace uking::ui {

// 0x71010a87f0
// NON_MATCHING: the original keeps the "type 18 while 19 is current" case as its own branch that jumps to the shared
// store; clang makes it a select
bool ScreenMessageTips::sub_71010A87F0(s32 type) {
    if ((type | 1) != 19)
        return false;

    if (type == 18 && _3a8 == 19)
        type = 19;
    if (_3a8 == type)
        _3ac = type;
    else
        type = _3ac;
    return type != 29;
}

}  // namespace uking::ui
