#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bd6340 (CSV eui::AnimButton::AnimButton)
AnimButton::AnimButton() {
    mFlags |= 0x2000;
}

// NON_MATCHING: same arithmetic; the original keeps the centre in integer registers and selects the base position
// offsets with branches (ours uses fcsel on float registers)
// 0x7100bd6798
bool AnimButton::HitTest(const sead::Vector2f& pos) const {
    const nn::ui2d::Pane* pane = mHitPane;
    if (!pane)
        return false;

    const auto& size = pane->GetSize();
    const auto& mtx = pane->GetMtx();
    const f32 width = size.width * mtx.m[0][0];
    const f32 height = size.height * mtx.m[1][1];
    const f32 half_width = (width > 0 ? width : -width) * 0.5f;
    const f32 half_height = (height > 0 ? height : -height) * 0.5f;

    f32 x = mtx.m[0][3];
    f32 y = mtx.m[1][3];
    const auto horizontal = pane->GetBasePositionH();
    if (horizontal == nn::ui2d::HorizontalPosition_Right)
        x = x - half_width;
    else if (horizontal == nn::ui2d::HorizontalPosition_Left)
        x = x + half_width;
    const auto vertical = pane->GetBasePositionV();
    if (vertical == nn::ui2d::VerticalPosition_Bottom)
        y = y + half_height;
    else if (vertical == nn::ui2d::VerticalPosition_Top)
        y = y - half_height;

    return x - half_width <= pos.x && pos.x <= half_width + x && y - half_height <= pos.y &&
           pos.y <= half_height + y;
}

// NON_MATCHING: same code; the immediate of the first flags mask on the `screen` path is -0x841 in the original, ours is
// narrowed to 0xf7bf
// 0x7100bd6384
void AnimButton::Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    mLayout = layout;
    Screen* screen = layout->mScreen;
    if (screen)
        mFlags = screen->_104 ? (mFlags | 0x40) : (mFlags & ~0x840);
    else
        mFlags &= ~0x840;
    mFlags &= ~0x800;

    BuildStateAnim(src, layout);
    mAnimators->SetSkipFirstFrameAll(true);
    mAnimators->SetSoundLinkAll(false);

    const char* disable_name = src.FindFunctionalAnimName("Disable");
    if (!disable_name || !*disable_name)
        disable_name = src.FindFunctionalAnimName("Invalid");
    if (disable_name && *disable_name) {
        mDisableAnim = layout->tryCreateAnimatorAutoWithWarning(disable_name, true);
        if (mDisableAnim)
            mDisableAnim->mFlags &= ~0x20;
    }

    const char* hit_name = src.FindFunctionalPaneName("Hit");
    mHitPane = layout->GetPane()->FindPaneByName(hit_name, true);

    const char* cursor_name = src.FindFunctionalPaneName("Cursor");
    if (cursor_name && *cursor_name && !layout->GetPane()->FindExtUserDataByName("BoxCursorOff")) {
        mBoxCursorPane = layout->GetPane()->FindPaneByName(cursor_name, true);
        sead::Heap* heap = GetNwAllocatorHeap();
        layout->mScreen->createBoxCursorNode(heap)->initialize(this, layout->mScreen);
    }

    mName = layout->GetPane()->GetParent() ? layout->GetPane()->GetName() : layout->mName;

    if (src.FindExtUserDataByName("RepeatOn"))
        mFlags |= 0x80;
    if (src.FindExtUserDataByName("NoTrigTouchOn"))
        mFlags |= 0x100;
    if (src.FindExtUserDataByName("DownWithTouchOn"))
        mFlags |= 0x200;
}

// 0x7100bd6f08
void AnimButton::CloneImpl_(const AnimButton& other, LayoutEx* layout, sead::Heap* heap) {
    mLayout = layout;
    SetTouch(other.mFlags & 0x40);

    mAnimators = new (heap) AnimatorSet(*other.mAnimators, layout, heap);
    mAnimators->SetSkipFirstFrameAll(true);
    mAnimators->SetSoundLinkAll(false);

    if (other.mDisableAnim) {
        mDisableAnim = layout->tryCreateAnimatorAutoWithWarning(other.mDisableAnim->mName, true);
        if (mDisableAnim)
            mDisableAnim->mFlags &= ~0x20;
    }

    if (other.mHitPane)
        mHitPane = layout->GetPane()->FindPaneByName(other.mHitPane->GetName(), true);

    if (other.mBoxCursorPane) {
        mBoxCursorPane = layout->GetPane()->FindPaneByName(other.mBoxCursorPane->GetName(), true);
        layout->mScreen->createBoxCursorNode(heap)->initialize(this, layout->mScreen);
    }

    mName = layout->GetPane()->GetParent() ? layout->GetPane()->GetName() : layout->mName;
}

// 0x7100bd6768
void AnimButton::Down() {
    ButtonBase::Down();
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

// 0x7100bd6cc8
bool AnimButton::ProcessOn() {
    switch (mState) {
    case kOff:
        StartOn();
        changeState(kStartOn);
        return true;
    case kStartOn:
        return true;
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        return true;
    case kOn:
        return true;
    case kStartDown:
        return false;
    case kDown:
        if (mFlags & 0x40) {
            StartOn();
            changeState(kStartOn);
        }
        return true;
    case kCancel:
        return false;
    default:
        return true;
    }
}

// 0x7100bd6d4c
bool AnimButton::ProcessOff() {
    switch (mState) {
    case kOff:
        return true;
    case kStartOn:
        StartOff();
        changeState(kStartOff);
        return true;
    case kStartOff:
        return true;
    case kOn:
        StartOff();
        changeState(kStartOff);
        return true;
    case kStartDown:
        return (mFlags >> 6) & 1;
    case kDown:
        return true;
    case kCancel:
        return true;
    default:
        return true;
    }
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
    Down();
    if (!(mFlags & 0x1000)) {
        if (!(screen && mBoxCursorPane && screen->moveBoxCursorByButton(this)))
            Off();
    }
    return true;
}

// 0x7100bd693c
void AnimButton::ActivateByBoxCursor() {
    mFlags = (mFlags & ~0x1840) | 0x1000;
    On();
}

// 0x7100bd695c
void AnimButton::InactivateByBoxCursor() {
    mFlags &= ~0x1000;
    Off();
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
