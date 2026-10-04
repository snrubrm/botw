#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a0a8d8
bool ScreenGameOver::sub_7100A0A8D8() {
    if (isOpening())
        return false;
    Screen::close(-1);
    return true;
}

// 0x7100a40bf8
bool ScreenReadyGo::sub_7100A40BF8() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    return animator && animator->mFrame >= 90.0f;
}

}  // namespace uking::ui
