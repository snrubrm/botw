#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// inline-only in the original; names are guesses (see ScreenKologNum)
static const ksys::StateBase& getShownState() {
    return sUnk_71025ef578;
}
static const ksys::StateBase& getHiddenState() {
    return sUnk_71025ef518;
}

// 0x7100a22a80
void ScreenMamoNum::sub_7100A22A80(s32 a1) {
    if (_3610 == 0)
        _3610 = ksys::gdt::getFlag_CurrentMamo(false);
    _3630 = a1;
    if (!isOpened()) {
        open(1);
        return;
    }
    if (a1 == 1) {
        _3614 = ksys::gdt::getFlag_CurrentMamo(false);
        mStateMachine.changeState(&sUnk_71025ef578);
        return;
    }
    const ksys::StateBase* state = mStateMachine.getState();
    if (state->getId() != getHiddenState().getId() && state->getId() != getShownState().getId())
        mStateMachine.changeState(&sUnk_71025ef518);
}

// 0x7100a22b98
bool ScreenMamoNum::sub_7100A22B98() {
    if (_3630 != 0)
        return false;
    if (mStateMachine.getState()->getId() == getShownState().getId()) {
        _3630 = 1;
        return false;
    }
    close(-1);
    return true;
}

}  // namespace uking::ui
