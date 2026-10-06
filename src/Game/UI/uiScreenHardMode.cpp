#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"

namespace uking::ui {

// 0x7100a0bc24
void ScreenHardMode::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Type", true);
    _3620 = mLayout->createAnimatorAuto("ContentOut", true);
    _3618 = mLayout->createAnimatorAuto("ContentIn", true);
    _3638 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnL_00"));
    _3640 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnR_00"));
    _3648 = mLayout;
    _3658 = sub_7100BEAFB0("Pa_BtnL_00");
    _3660 = sub_7100BEAFB0("Pa_BtnR_00");
    _3718 = -1;
    _3700 = -1;
    _3704 = 0;
    _3668.clear();
    mStateMachine.startState(&sUnk_710261ee98);
}

// 0x7100a0bb1c (CSV ScreenHardMode::m6)
void ScreenHardMode::close(s32) {
    if (_3721)
        Screen::close(-1);
}

// 0x7100a0bd2c
void ScreenHardMode::m98() {
    setReservedBoxCursorNodeByButton(_3638);
    mActiveCursorNode = nullptr;
}

// 0x7100a0bd54
void ScreenHardMode::m99() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a0befc
void ScreenHardMode::m106(eui::AnimButton* button) {
    mButtonGroup->_38 &= ~2;
    const s32 tag = button->mTag;
    switch (tag) {
    case 0x8f:
        invokeSoundLink2Event_("mc_Cancel");
        _3718 = 0x8f;
        _3721 = 0;
        [[fallthrough]];
    case 0x8e:
    case 0x90:
        if (_3720)
            invokeSoundLink2Event_("mc_GameStart");
        else
            invokeSoundLink2Event_("mc_Decide");
        _3718 = tag;
        _3721 = 0;
        break;
    }
}

// 0x7100a0bfa8
void ScreenHardMode::m107(eui::AnimButton* button) {
    if (u32(button->mTag - 0x8e) <= 2)
        _3721 = 1;
}

// 0x7100a0ce70
void ScreenHardMode::m203() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cf90
void ScreenHardMode::m210() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(4);
    _371c = 0;
}

// 0x7100a0cfd0
void ScreenHardMode::m214() {
    _3710 = mStateMachine.getState();
    _3704 = _3708;
    x();
}

// 0x7100a0d004
void ScreenHardMode::m215() {
    if (mState != 0 && mState != 3) {
        if (_371c++ >= 59) {
            _3704 = _3708;
            x();
        }
    }
}

// 0x7100a0d0b0
void ScreenHardMode::m219() {
    switch (_3718) {
    case 0x90:
        _3704 = 5;
        mStateMachine.changeState(&sUnk_71025ee930);
        break;
    case 0x8f:
        mStateMachine.changeState(&sUnk_71025ee810);
        break;
    }
}

// 0x7100a0c660
void ScreenHardMode::m155() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        mStateMachine.changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c784
void ScreenHardMode::m163() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        mStateMachine.changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cb28
void ScreenHardMode::m183() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        mStateMachine.changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c844
void ScreenHardMode::m167() {
    switch (_3718) {
    case 0x90:
        mStateMachine.changeState(&sUnk_71025ee330);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cd00
void ScreenHardMode::m195() {
    switch (_3718) {
    case 0x90:
        mStateMachine.changeState(&sUnk_71025ee5d0);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c888
void ScreenHardMode::m170() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0c9fc
void ScreenHardMode::m178() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0cd44
void ScreenHardMode::m198() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0ceb0
void ScreenHardMode::m206() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d0f4
void ScreenHardMode::m222() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d1c0
void ScreenHardMode::m226() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d294
void ScreenHardMode::m230() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d368
void ScreenHardMode::m234() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(4);
}

// 0x7100a0d3a0
void ScreenHardMode::m238() {
    _3710 = mStateMachine.getState();
    sub_7100A0BFC8(0);
}

// 0x7100a0c6f8 (CSV ScreenHardMode::m159)
void ScreenHardMode::m159() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c9bc
void ScreenHardMode::m175() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cbc0
void ScreenHardMode::m187() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cc4c
void ScreenHardMode::m191() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

void ScreenHardMode::m156() {}

void ScreenHardMode::m160() {}

void ScreenHardMode::m164() {}

void ScreenHardMode::m168() {}

void ScreenHardMode::m172() {}

void ScreenHardMode::m176() {}

void ScreenHardMode::m180() {}

void ScreenHardMode::m184() {}

void ScreenHardMode::m188() {}

void ScreenHardMode::m192() {}

void ScreenHardMode::m196() {}

void ScreenHardMode::m200() {}

void ScreenHardMode::m204() {}

void ScreenHardMode::m208() {}

void ScreenHardMode::m211() {}

void ScreenHardMode::m212() {}

void ScreenHardMode::m216() {}

void ScreenHardMode::m220() {}

void ScreenHardMode::m224() {}

void ScreenHardMode::m228() {}

void ScreenHardMode::m232() {}

void ScreenHardMode::m235() {}

void ScreenHardMode::m236() {}

void ScreenHardMode::m240() {}

void ScreenHardMode::m242() {}

void ScreenHardMode::m243() {}

void ScreenHardMode::m244() {}

bool ScreenHardMode::isEnableControl() const {
    return 1;
}

s32 ScreenHardMode::m157() {
    return 0;
}

s32 ScreenHardMode::m161() {
    return 0;
}

s32 ScreenHardMode::m165() {
    return 0;
}

s32 ScreenHardMode::m169() {
    return 0;
}

s32 ScreenHardMode::m173() {
    return 0;
}

s32 ScreenHardMode::m177() {
    return 0;
}

s32 ScreenHardMode::m181() {
    return 0;
}

s32 ScreenHardMode::m185() {
    return 0;
}

s32 ScreenHardMode::m189() {
    return 0;
}

s32 ScreenHardMode::m193() {
    return 0;
}

s32 ScreenHardMode::m197() {
    return 0;
}

s32 ScreenHardMode::m201() {
    return 0;
}

s32 ScreenHardMode::m205() {
    return 0;
}

s32 ScreenHardMode::m209() {
    return 0;
}

s32 ScreenHardMode::m213() {
    return 0;
}

s32 ScreenHardMode::m217() {
    return 0;
}

s32 ScreenHardMode::m221() {
    return 0;
}

s32 ScreenHardMode::m225() {
    return 0;
}

s32 ScreenHardMode::m229() {
    return 0;
}

s32 ScreenHardMode::m233() {
    return 0;
}

s32 ScreenHardMode::m237() {
    return 0;
}

s32 ScreenHardMode::m241() {
    return 0;
}

s32 ScreenHardMode::m245() {
    return 0;
}

}  // namespace uking::ui
