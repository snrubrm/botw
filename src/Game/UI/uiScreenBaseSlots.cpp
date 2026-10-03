#include "Game/UI/uiScreens.h"

namespace eui {

// 0x7100be9a4c (CSV eui::Screen::x)
void Screen::m13() {}

}  // namespace eui

namespace uking::ui {

// 0x71010ab24c (CSV Screen::updateButton)
void Screen::m50() {
    if (_292 & 4)
        updateButton_();
}

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

// 0x71010aada0 (CSV Screen::m117)
void Screen::m117() {
    m82();
    for (auto& child : mChildren)
        child.m43();
}

// 0x71010aadf0 (CSV Screen::m118)
void Screen::m118() {
    m83();
    for (auto& child : mChildren)
        child.m44();
}

// 0x71010aae40 (CSV Screen::m119)
void Screen::m119() {
    m84();
    for (auto& child : mChildren)
        child.m45();
}

// 0x71010aae90 (CSV Screen::m120)
void Screen::m120() {
    m85();
    for (auto& child : mChildren)
        child.m46();
}

// 0x71010aaf54 (CSV Screen::m122)
void Screen::m122() {
    m87();
    for (auto& child : mChildren)
        child.m48();
}

// 0x71010aafa4 (CSV Screen::m123)
void Screen::m123() {
    m88();
    for (auto& child : mChildren)
        child.m49();
}

// 0x71010aaff4 (CSV Screen::m124)
void Screen::m124() {
    m89();
    for (auto& child : mChildren)
        child.m50();
}

// 0x71010ab044 (CSV Screen::m125)
void Screen::m125() {
    m90();
    for (auto& child : mChildren)
        child.m51();
}

// 0x71010ab094 (CSV Screen::m126)
void Screen::m126() {
    m91();
    for (auto& child : mChildren)
        child.m52();
}

// 0x71010aaee0 (CSV Screen::m121)
void Screen::m121() {
    if (!ksys::ui::sub_7100EDC564(mId))
        close(-4);
    m86();
    for (auto& child : mChildren)
        child.m47();
}

// 0x71010ab0e4 (CSV Screen::open)
void Screen::open(s32 option) {
    _290 = 0;
    if (ksys::ui::sub_7100EDC548(mId))
        _292 &= ~0x20;
    eui::Screen::open(option);
}

// 0x7100a828f4 (CSV Screen::m111)
s32 Screen::m111() {
    return 0;
}

// 0x7100a828fc (CSV Screen::m112_null)
void Screen::m112() {}

// 0x7100a82900 (CSV Screen::m113_null)
void Screen::m113() {}

// 0x7100a82904 (CSV Screen::m114_null)
void Screen::m114() {}

// 0x7100a82908 (CSV Screen::m115_null)
void Screen::m115() {}

// 0x7100a8290c (CSV Screen::m116_null)
void Screen::m116() {}

}  // namespace uking::ui
