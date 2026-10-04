#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bda964
TwoTouchCheckKeepButton::TwoTouchCheckKeepButton() = default;

// 0x7100bda9ac
TwoTouchCheckKeepButton::TwoTouchCheckKeepButton(const TwoTouchCheckKeepButton& other,
                                                 LayoutEx* layout, sead::Heap* heap)
    : CheckKeepButton(other, layout, heap) {
    mTouchAnimators = new (heap) AnimatorSet(*other.mTouchAnimators, layout, heap);
    mTouchAnimators->SetSkipFirstFrameAll(true);
    mTouchAnimators->SetSoundLinkAll(false);
    Animator* current = mTouchAnimators->mCurrent;
    current->nn::ui2d::AnimTransform::SetEnabled(false);
    current->mRate = 0;
    mNormalAnimators = mAnimators;
}

// 0x7100bdaa60
bool TwoTouchCheckKeepButton::HitTest(const sead::Vector2f& pos) const {
    if (mState == kCancel)
        return false;
    return AnimButton::HitTest(pos);
}

// 0x7100bdaa78
void TwoTouchCheckKeepButton::ActivateByBoxCursor() {
    if (mFlags & 0x40) {
        mAnimators = mNormalAnimators;
        mUseTouch = false;
    }
    AnimButton::ActivateByBoxCursor();
}

// 0x7100bdaa90
void TwoTouchCheckKeepButton::InactivateByBoxCursor() {
    AnimButton::InactivateByBoxCursor();
    if ((mFlags & 0x40) && mChecked && mState == kStartDown)
        ForceOff();
}

// 0x7100bdaae4
void TwoTouchCheckKeepButton::BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    AnimButton::BuildStateAnim(src, layout);
    const char* names[8] = {
        src.FindFunctionalAnimName("TouchOn2"),     src.FindFunctionalAnimName(""),
        src.FindFunctionalAnimName("TouchOff2"),    src.FindFunctionalAnimName(""),
        src.FindFunctionalAnimName("TouchDecide2"), src.FindFunctionalAnimName(""),
        src.FindFunctionalAnimName("TouchCancel"),  src.FindFunctionalAnimName(""),
    };
    mTouchAnimators = layout->createAnimatorSet(names, 8, true);
    mTouchAnimators->SetSkipFirstFrameAll(true);
    mTouchAnimators->SetSoundLinkAll(false);
    Animator* current = mTouchAnimators->mCurrent;
    current->nn::ui2d::AnimTransform::SetEnabled(false);
    current->mRate = 0;
    mNormalAnimators = mAnimators;
}

// NON_MATCHING: the original tests the kOff state last (cbnz) instead of first (cbz)
// 0x7100bdac00
bool TwoTouchCheckKeepButton::ProcessCancel() {
    if (!(mFlags & 0x40) || !mUseTouch)
        return AnimButton::ProcessCancel();
    switch (mState) {
    case kStartOn:
    case kStartOff:
    case kOn:
    case kStartDown:
    case kDown:
        return false;
    case kCancel:
        return true;
    case kOff:
        StartCancel();
        changeState(kCancel);
        return true;
    default:
        return true;
    }
}

// 0x7100bdac88
void TwoTouchCheckKeepButton::StartDown() {
    if (!(mFlags & 0x40) || mUseTouch)
        CheckKeepButton::StartDown();
    else
        AnimButton::StartDown();
}

// 0x7100bdaca0
bool TwoTouchCheckKeepButton::UpdateDown() {
    if (!(mFlags & 0x40) || mUseTouch)
        return CheckButton::UpdateDown();
    return AnimButton::UpdateDown();
}

// 0x7100bdacb8
void TwoTouchCheckKeepButton::FinishDown() {
    if ((mFlags & 0x40) && !mUseTouch) {
        mAnimators = mTouchAnimators;
        mUseTouch = true;
    }
    AnimButton::FinishDown();
}

// 0x7100bdad08
bool TwoTouchCheckKeepButton::UpdateCancel() {
    return mAnimators->mCurrent->mFlags & 1;
}

// 0x7100bdacdc
void TwoTouchCheckKeepButton::StartCancel() {
    mAnimators->select(6)->Play(Animator::PlayType(0), 1.0f);
}

// 0x7100bdad1c
void TwoTouchCheckKeepButton::FinishCancel() {
    mUseTouch = false;
    mAnimators = mNormalAnimators;
    selectStateAnim(0)->StopAtMin();
    changeState(kOff);
}

}  // namespace eui
