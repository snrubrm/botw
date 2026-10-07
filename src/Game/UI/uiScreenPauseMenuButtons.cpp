#include "Game/UI/uiScreens.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"

namespace uking::ui {

ScreenButton_7100989968::ScreenButton_7100989968() = default;
ScreenButton_7100989968::~ScreenButton_7100989968() = default;

void ScreenButton_7100989968::sub_710098923C() {
    if (mAnimator) {
        if (mAnimator->mFrame != mAnimator->GetFrameSize())
            mAnimator->StopAtMax();
        if (_28)
            _28->StopAtMax();
    }
}

void ScreenButton_7100989968::sub_71009892B0() {
    if (mAnimator) {
        if (mAnimator->mFrame != 0.0f)
            mAnimator->StopAtMin();
        if (_28)
            _28->StopAtMax();
        mButton->setFlag10(false);
    }
}


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

void ScreenButton_7100989968::sub_71009896D8() {
    if (_10 && _10->mFrame != 0.0f)
        _10->StopAtMin();
    if (_18 && _18->mFrame != 0.0f)
        _18->StopAtMin();
    mBreakNewController.sub_71009B1578(-1);
    mTexturePatternController.sub_7100988FE8();
    mCategoryController.sub_7100989AF0(-1, 0, 0);
}

// NON_MATCHING: the compiler shares the Animator frame load across enabled/disabled branches.
void ScreenButton_7100989968::sub_7100989888(bool enabled, bool play) {
    if (!_10)
        return;
    if (enabled) {
        if (_10->mFrame == _10->GetFrameSize())
            return;
        if (play)
            _10->PlayAuto(1.0f);
        else
            _10->StopAtMax();
    } else {
        if (_10->mFrame == 0.0f)
            return;
        if (play)
            _10->PlayAuto(-1.0f);
        else
            _10->StopAtMin();
    }
}

bool ScreenButton_7100989968::sub_7100989A08() const {
    return mAnimator && mAnimator->mFrame == mAnimator->GetFrameSize();
}

void ScreenButton_7100989968::sub_7100989A40() {
    if (_28)
        _28->PlayAuto(1.0f);
}

}  // namespace uking::ui
