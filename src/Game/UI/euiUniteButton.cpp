#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bdae2c
UniteButton::UniteButton() = default;

// 0x7100bdb254
void UniteButton::Uncheck() {
    if (mType <= 1 && mChecked && !IsPlayDisableAnim()) {
        if (mCheckAnim)
            mCheckAnim->Play(Animator::PlayType(0), -1.0f);
        mChecked = false;
    }
}

// 0x7100bdb2b0
void UniteButton::ForceSetChecked(bool checked) {
    mChecked = checked;
    if (mCheckAnim) {
        if (checked)
            mCheckAnim->StopAtMax();
        else
            mCheckAnim->StopAtMin();
    }
}

// 0x7100bdb2dc
void UniteButton::StartDrag(const sead::Vector2f& pos) {
    nn::ui2d::Pane* pane = mLayout->mPane;
    mStartPos = pos;
    const auto& position = pane->GetPosition();
    mPanePos = {position.x, position.y};
    if (mDragAnim)
        mDragAnim->Play(Animator::PlayType(0), 1.0f);
}

// 0x7100bdb374
void UniteButton::FinishDrag(const sead::Vector2f* pos) {
    if (mFlags & 0x40)
        Off();
    else
        Cancel();
    if (mDragAnim)
        mDragAnim->PlayFromCurrent(Animator::PlayType(0), -1.0f);
}

// 0x7100bdb3d4
bool UniteButton::HitTest(const sead::Vector2f& pos) const {
    if (mType == 5 || mType == 3) {
        if (mState == kCancel)
            return false;
    }
    return AnimButton::HitTest(pos);
}

// 0x7100bdb3fc
void UniteButton::BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    const char* names[8] = {
        src.FindFunctionalAnimName("Select"),   src.FindFunctionalAnimName("TouchSelect"),
        src.FindFunctionalAnimName("UnSelect"), src.FindFunctionalAnimName("TouchUnSelect"),
        src.FindFunctionalAnimName("Decide"),   src.FindFunctionalAnimName("TouchDecide"),
        src.FindFunctionalAnimName("Cancel"),   src.FindFunctionalAnimName("TouchCancel"),
    };
    mAnimators = layout->createAnimatorSet(names, 8, true);
}

// 0x7100bdb4ec
void UniteButton::StartDown() {
    AnimButton::StartDown();
    if (mType == 0 || (mType == 1 && !mChecked)) {
        if (!IsPlayDisableAnim()) {
            if (mCheckAnim)
                mCheckAnim->Play(Animator::PlayType(0), mChecked ? -1.0f : 1.0f);
            mChecked = !mChecked;
        }
    }
}

// 0x7100bdb570
bool UniteButton::UpdateDown() {
    bool done = AnimButton::UpdateDown();
    if (mType <= 1) {
        if (mChecked)
            done = done && mCheckAnim->mFrame == f32(mCheckAnim->GetFrameSize());
        else
            done = done && mCheckAnim->mFrame == 0.0f;
    }
    return done;
}

// 0x7100bdb5ec
void UniteButton::FinishDown() {
    if (mType == 5 || mType == 3)
        changeState(kDown);
    else if (mType == 2)
        changeState(kDown);
    else
        AnimButton::FinishDown();
}

// 0x7100bdb618
void UniteButton::StartCancel() {
    if (mType == 5 || mType == 3) {
        if (mAnimators->mAnimators[6] || mAnimators->mAnimators[7])
            selectStateAnim(6)->Play(Animator::PlayType(0), 1.0f);
    } else {
        ButtonBase::StartCancel();
    }
}

// 0x7100bdb68c
bool UniteButton::UpdateCancel() {
    if (mType == 5 || mType == 3) {
        if (mAnimators->mAnimators[6] || mAnimators->mAnimators[7])
            return mAnimators->mCurrent->mFlags & 1;
        return true;
    }
    return ButtonBase::UpdateCancel();
}

// 0x7100bdb6ec
void UniteButton::FinishCancel() {
    if (mType == 5 || mType == 3) {
        selectStateAnim(0)->StopAtMin();
        changeState(kOff);
    } else {
        ButtonBase::FinishCancel();
    }
}

// NON_MATCHING: clang tests `type == 2` first (the original: 5 / 3 first, 2 last)
// 0x7100bdb750
bool UniteButton::ProcessOn() {
    if (mType == 5 || mType == 3) {
        if (mState == kDown)
            return true;
    } else if (mType == 2) {
        if ((mState & 0xfe) == kStartDown)
            return true;
    }
    return AnimButton::ProcessOn();
}

// 0x7100bdb794
bool UniteButton::ProcessOff() {
    if (mType <= 5 && ((1 << mType) & 0x2c)) {
        if ((mState & 0xfe) == kStartDown)
            return true;
    }
    return AnimButton::ProcessOff();
}

// NON_MATCHING: clang tests `state == 4` before `state == 5` (the original: 5 first)
// 0x7100bdb7d0
bool UniteButton::ProcessCancel() {
    if (mType == 5 || mType == 3) {
        if (mState == kDown) {
            StartCancel();
            changeState(kCancel);
        } else if (mState == kStartDown) {
            return false;
        }
    }
    return true;
}

}  // namespace eui
