#include "Game/UI/uiScreens.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"

namespace uking::ui {

// 0x710098993c
void ScreenButton_7100989968::sub_710098993C(bool enabled, bool play) {
    if (!mButton)
        return;
    if (play)
        mButton->PlayDisableAnim(enabled);
    else
        mButton->StopDisableAnim(enabled);
}

// 0x7100989968
void ScreenButton_7100989968::sub_7100989968(bool enabled) {
    if (!mButton)
        return;
    if (mAnimator && mAnimator->mFrame == f32(mAnimator->GetFrameSize()))
        mButton->setFlag10(enabled);
    else
        mButton->setFlag10(false);
}

// 0x71009899ec
void ScreenButton_7100989968::sub_71009899EC() {
    if (mAnimator)
        mAnimator->PlayAuto(1.0f);
}

}  // namespace uking::ui
