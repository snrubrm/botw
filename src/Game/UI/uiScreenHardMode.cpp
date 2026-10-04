#include "Game/UI/uiScreens.h"

namespace uking::ui {

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

s32 ScreenHardMode::isEnableControl() const {
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
