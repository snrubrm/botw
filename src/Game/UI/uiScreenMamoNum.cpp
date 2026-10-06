#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x7100a22888
void ScreenMamoNum::m93(sead::Heap*) {
    _3618.init(5.0f);
    mStateMachine.startState(&sUnk_71025ef4b8);
    _3638.sub_71009331C(sub_7100BEAFB0("Pa_PlusMinus_00"),
                        eui::sub_7100933580(mLayout->mPane->FindPaneByName("T_Num_00", true)));
    _3638.set30(mLayout->tryCreateAnimatorAuto("Flash", false));
    _3678.sub_71009319C(0, "mc_CountUpMamo", "mc_CountUpMamoEnd");
    _3678.sub_71009319C(1, "mc_CountDownMamo", "mc_CountDownMamoEnd");
}

// 0x7100a22f28
void ScreenMamoNum::m162() {
    _3618.init(5.0f);
}

// 0x7100a22f38
void ScreenMamoNum::m163() {
    if (getFlagInt(&_3614, ksys::gdt::flagname::CurrentMamo())) {
        mStateMachine.changeState(&sUnk_71025ef578);
    } else if (_3618.updateAndCheckEnded()) {
        close(-1);
    }
}

// 0x7100a22a80
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
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
    if (state->getId() != sUnk_71025ef518.getId() && state->getId() != sUnk_71025ef578.getId())
        mStateMachine.changeState(&sUnk_71025ef518);
}

// 0x7100a22b98
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
bool ScreenMamoNum::sub_7100A22B98() {
    if (_3630 != 0)
        return false;
    if (mStateMachine.getState()->getId() == sUnk_71025ef578.getId()) {
        _3630 = 1;
        return false;
    }
    close(-1);
    return true;
}

}  // namespace uking::ui
