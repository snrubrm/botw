#include "Game/UI/uiScreens.h"

namespace eui {

// 0x7100be9a4c (CSV eui::Screen::x)
void Screen::m13() {}

}  // namespace eui

namespace uking::ui {

// 0x71010ab25c (CSV Screen::updateControl)
void Screen::m51() {
    if (_292 & 8)
        updateControl_();
}

// 0x71010ab26c (CSV Screen::updateAnimator)
void Screen::m59() {
    if (_292 & 0x10)
        updateAnimator_();
}

// 0x71010aacac (CSV Screen::m76)
void Screen::m76() {
    _270 = 0;
    close(-4);
}

// 0x71010aad78 (CSV Screen::m79)
void Screen::m79() {
    _288 = nullptr;
}

// 0x71010aad80 (CSV Screen::m89)
void Screen::m89() {
    _292 |= 0x20;
    _290 = 0;
    mMgr->inactivateScreen(mId);
}

// 0x7100a82904 (CSV Screen::m114_null)
void Screen::m114() {}

// 0x7100a82908 (CSV Screen::m115_null)
void Screen::m115() {}

// 0x7100a8290c (CSV Screen::m116_null)
void Screen::m116() {}

}  // namespace uking::ui
