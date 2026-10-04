#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// inline-only in the original; names are guesses (see ScreenKologNum::getShownState)
static const ksys::StateBase& getShortCutState0() {
    return sUnk_71025ef170;
}
static const ksys::StateBase& getShortCutState1() {
    return sUnk_71025ef290;
}
static const ksys::StateBase& getToolState() {
    return sUnk_71025ec670;
}

// 0x7100a20dd0
bool ScreenMainShortCut::sub_7100A20DD0() {
    if (mStateMachine.getState()->getId() == getShortCutState0().getId())
        return false;
    return mStateMachine.getState()->getId() != getShortCutState1().getId();
}

// 0x71009fd674
bool ScreenAppTool::sub_71009FD674() {
    return mStateMachine.getState()->getId() == getToolState().getId();
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
