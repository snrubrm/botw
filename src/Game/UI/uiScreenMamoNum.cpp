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

// 0x7100a229c8
void ScreenMamoNum::m94() {
    if (isOpened() && sub_7100A98038(mId)) {
        if (mState != 0 && mState != 3) {
            const s32 count = ksys::gdt::getFlag_CurrentMamo(false);
            _3614 = count;
            _3610 = count;
            sub_7100AA930C(mLayout, "T_Num_00", count, 0, 0);
            close(-1);
        }
        return;
    }
    mStateMachine.run();
}

// 0x7100a22c20
void ScreenMamoNum::m98() {
    sub_7100AA930C(mLayout, "T_Num_00", _3610, 0, 0);
    _3638.sub_71009333AC();
}

// 0x7100a22c80
void ScreenMamoNum::m99() {
    if (_3630 == 1) {
        _3614 = ksys::gdt::getFlag_CurrentMamo(false);
        mStateMachine.changeState(&sUnk_71025ef578);
        return;
    }
    const ksys::StateBase* state = mStateMachine.getState();
    // called through a pointer in the original (not devirtualised)
    if (state->getId() != (&sUnk_71025ef518)->getId() && state->getId() != (&sUnk_71025ef578)->getId())
        mStateMachine.changeState(&sUnk_71025ef518);
}

// 0x7100a22d80
void ScreenMamoNum::m155() {
    const s32 count = ksys::gdt::getFlag_CurrentMamo(false);
    const bool changed = _3610 != count;
    _3614 = count;
    if (changed)
        mStateMachine.changeState(&sUnk_71025ef578);
}

// 0x7100a22dd0
void ScreenMamoNum::m158() {
    _3638.set38(_3614 - _3610);
}

// 0x7100a22dec
void ScreenMamoNum::m159() {
    if (sub_7100AA8F70())
        return;
    const s32 old_count = _3614;
    if (getFlagInt(&_3614, ksys::gdt::flagname::CurrentMamo())) {
        _3638.set38(_3614 - old_count);
    }
    _3638.sub_71009333CC();
    const s32 step = sub_7100AA92AC(_3610, _3614);
    _3610 += step;
    sub_7100AA930C(mLayout, "T_Num_00", _3610, _3614, step);
    if (_3610 == _3614) {
        _3678.sub_7100933294();
        if (_3630 == 1)
            mStateMachine.changeState(&sUnk_71025ef5d8);
        else
            mStateMachine.changeState(&sUnk_71025ef518);
    } else {
        if (_3638._3c)
            _3678.sub_71009331E8(0);
        else
            _3678.sub_71009331E8(1);
    }
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
    // called through a pointer in the original (not devirtualised)
    if (state->getId() != (&sUnk_71025ef518)->getId() && state->getId() != (&sUnk_71025ef578)->getId())
        mStateMachine.changeState(&sUnk_71025ef518);
}

// 0x7100a22b98
bool ScreenMamoNum::sub_7100A22B98() {
    if (_3630 != 0)
        return false;
    // called through a pointer in the original (not devirtualised)
    if (mStateMachine.getState()->getId() == (&sUnk_71025ef578)->getId()) {
        _3630 = 1;
        return false;
    }
    close(-1);
    return true;
}

}  // namespace uking::ui
