#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bd6340 (CSV eui::AnimButton::AnimButton)
AnimButton::AnimButton() {
    mFlags |= 0x2000;
}

// 0x7100bd6768
void AnimButton::requestDown() {
    ButtonBase::requestDown();
    mFlags &= ~0x4000;
}

// 0x7100bd65c0
void AnimButton::SetTouch(bool touch) {
    mFlags = touch ? (mFlags | 0x40) : (mFlags & ~0x40);
    mFlags &= ~0x800;
}

// 0x7100bd6a10
Animator* AnimButton::selectStateAnim(u32 idx) {
    if (mFlags & 0x40) {
        if (mAnimators->mAnimators[idx + 1])
            return mAnimators->select(idx + 1);
    }
    return mAnimators->select(idx);
}

// 0x7100bd69b0
void AnimButton::ForceOff() {
    ButtonBase::ForceOff();
    selectStateAnim(0)->StopAtMin();
}

// 0x7100bd6a48
void AnimButton::ForceOn() {
    ButtonBase::ForceOn();
    selectStateAnim(0)->StopAtMax();
}

// 0x7100bd6aa8
void AnimButton::ForceDown() {
    ButtonBase::ForceDown();
    selectStateAnim(4)->StopAtMax();
}

// 0x7100bd6b08
void AnimButton::StartOn() {
    AnimatorSet* set = mAnimators;
    Animator* anim = set->mAnimators[2];
    if (anim)
        selectStateAnim(0)->Play(Animator::PlayType(0), 1.0f);
    else
        selectStateAnim(0)->PlayFromCurrent(Animator::PlayType(0), 1.0f);
}

// 0x7100bd6b88
void AnimButton::StartOff() {
    AnimatorSet* set = mAnimators;
    Animator* anim = set->mAnimators[2];
    if (anim)
        selectStateAnim(2)->Play(Animator::PlayType(0), 1.0f);
    else
        selectStateAnim(0)->PlayFromCurrent(Animator::PlayType(0), -1.0f);
}

// 0x7100bd6c34
void AnimButton::StartDown() {
    selectStateAnim(4)->Play(Animator::PlayType(0), 1.0f);
}

// 0x7100bd6dc0
void AnimButton::FinishDown() {
    if (mFlags & 0x40) {
        mAnimators->select(mAnimators->mAnimators[1] != nullptr)->StopAtMin();
        changeState(kDown);
        changeState(kOff);
    } else {
        changeState(kDown);
        changeState(kOn);
    }
}

// NON_MATCHING: the original places the shared StartOn block before the other case blocks
// 0x7100bd6cc8
bool AnimButton::ProcessOn() {
    bool handled = true;
    switch (mState) {
    case kOff:
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        break;
    case kStartDown:
    case kCancel:
        handled = false;
        break;
    case kDown:
        if (!(mFlags & 0x40))
            break;
        StartOn();
        changeState(kStartOn);
        break;
    default:
        break;
    }
    return handled;
}

// 0x7100bd6d4c
bool AnimButton::ProcessOff() {
    if (mState == kStartDown)
        return (mFlags >> 6) & 1;
    if (mState == kStartOn) {
        StartOff();
        changeState(kStartOff);
    } else if (mState == kOn) {
        StartOff();
        changeState(kStartOff);
    }
    return true;
}

// 0x7100bd6e64
void AnimButton::changeState(State state) {
    State old_state = State(mState);
    if (old_state == state)
        return;
    if ((state | 2) == 2) {
        if (mFlags & 0x800)
            mFlags = (mFlags & ~0x840) | 0x40;
    }
    if (Screen* screen = mLayout->mScreen)
        screen->buttonStateChangeCallback(this, old_state, state);
    mState = state;
}

// 0x7100bd6ed0
void AnimButton::setState(State state) {
    if (mState == state)
        return;
    if ((state | 2) == 2) {
        if (mFlags & 0x800)
            mFlags = (mFlags & ~0x840) | 0x40;
    }
    mState = state;
}

// 0x7100bd66ac
bool AnimButton::DownOff(bool b) {
    if ((mFlags & 0x14) != 0x14)
        return false;
    Screen* screen = mLayout->mScreen;
    if (screen) {
        if (screen->mButtonGroup->IsExistExcludingDown())
            return false;
    }
    if (b && (mFlags & 0x40))
        mFlags = (mFlags & ~0x40) | 0x800;
    requestDown();
    if (!(mFlags & 0x1000)) {
        if (!(screen && mBoxCursorPane && screen->moveBoxCursorByButton(this)))
            requestOff();
    }
    return true;
}

// 0x7100bd693c
void AnimButton::ActivateByBoxCursor() {
    mFlags = (mFlags & ~0x1840) | 0x1000;
    requestOn();
}

// 0x7100bd695c
void AnimButton::InactivateByBoxCursor() {
    mFlags &= ~0x1000;
    requestOff();
    if (mLayout->mScreen->_104)
        mFlags |= 0x800;
}

// 0x7100bd68f0
bool AnimButton::IsPlayDisableAnim() const {
    Animator* anim = mDisableAnim;
    if (!anim)
        return false;
    if (anim->mRate > 0.0f)
        return true;
    return anim->mFrame == f32(anim->GetFrameSize());
}

// 0x7100bd65e8
void AnimButton::BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    const char* names[6] = {
        src.FindFunctionalAnimName("On"),     src.FindFunctionalAnimName("TouchOn"),
        src.FindFunctionalAnimName("Off"),    src.FindFunctionalAnimName("TouchOff"),
        src.FindFunctionalAnimName("Decide"), src.FindFunctionalAnimName("TouchDecide"),
    };
    mAnimators = layout->createAnimatorSet(names, 6, true);
}

// 0x7100bd68a0
void AnimButton::PlayDisableAnim(bool play) {
    if (!mDisableAnim)
        return;
    mDisableAnim->PlayFromCurrent(Animator::PlayType(0), play ? 1.0f : -1.0f);
}

// 0x7100bd68cc
void AnimButton::StopDisableAnim(bool atEnd) {
    if (!mDisableAnim)
        return;
    if (atEnd)
        mDisableAnim->StopAtMax();
    else
        mDisableAnim->StopAtMin();
}

// 0x7100bd6c8c / 0x7100bd6ca0 / 0x7100bd6cb4
bool AnimButton::UpdateOn() {
    return mAnimators->mCurrent->mFlags & 1;
}
bool AnimButton::UpdateOff() {
    return mAnimators->mCurrent->mFlags & 1;
}
bool AnimButton::UpdateDown() {
    return mAnimators->mCurrent->mFlags & 1;
}

// 0x7100bd6db8
bool AnimButton::ProcessCancel() {
    return true;
}

}  // namespace eui
