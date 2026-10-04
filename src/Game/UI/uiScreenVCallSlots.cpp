#include "Game/UI/uiScreens.h"

// Slots that forward to open() / close() with a constant argument.
namespace uking::ui {

// 0x7100a0b1c4
void ScreenGamePadBG::m82() {
    open(1);
}

// 0x7100a11ed4
void ScreenMainScreen3D::m84() {
    open(1);
}

// 0x7100a2bea8
void ScreenPauseMenuBG::m82() {
    open(4);
}

// 0x7100a2beb8
void ScreenPauseMenuBG::m83() {
    open(4);
}

// 0x7100a4aa20
void ScreenSeekPadMenuBG::m82() {
    open(4);
}

// 0x7100a4aa30
void ScreenSeekPadMenuBG::m83() {
    open(4);
}

// 0x7100a2c2b0
void ScreenPauseMenuEiketsu::m107(eui::AnimButton*) {
    close(-1);
}

}  // namespace uking::ui
