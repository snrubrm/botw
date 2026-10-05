#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a0a75c
void ScreenGameOver::m101() {
    _3610 = 0;
    _3614 = 7;
}

// 0x7100a0a8d8
bool ScreenGameOver::sub_7100A0A8D8() {
    if (isOpening())
        return false;
    Screen::close(-1);
    return true;
}

// 0x7100a0a914
bool ScreenGameOver::sub_7100A0A914() {
    return !_3620 || _3620->GetAlpha() == 255;
}

// 0x7100a0a9a8
void ScreenGameOver::m156() {
    if (_3610)
        return;
    if (auto* button = mButtonGroup->FindButtonByTag(120))
        button->setFlag10(false);
    if (auto* button = mButtonGroup->FindButtonByTag(121))
        button->setFlag10(false);
}

// 0x7100a40bf8
bool ScreenReadyGo::sub_7100A40BF8() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    return animator && animator->mFrame >= 90.0f;
}

}  // namespace uking::ui
