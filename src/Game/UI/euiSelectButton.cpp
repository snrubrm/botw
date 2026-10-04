#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bd9e3c
SelectButton::SelectButton(const SelectButton& other, LayoutEx* layout, sead::Heap* heap) {
    CloneImpl_(other, layout, heap);
}

// 0x7100bd9e90
void SelectButton::BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    const char* names[7] = {
        src.FindFunctionalAnimName("On"),     src.FindFunctionalAnimName("TouchOn"),
        src.FindFunctionalAnimName("Off"),    src.FindFunctionalAnimName("TouchOff"),
        src.FindFunctionalAnimName("Decide"), src.FindFunctionalAnimName("TouchDecide"),
        src.FindFunctionalAnimName("Cancel"),
    };
    mAnimators = layout->createAnimatorSet(names, 7, true);
}

// 0x7100bd9f68
bool SelectButton::HitTest(const sead::Vector2f& pos) const {
    if (mState == kCancel)
        return false;
    return AnimButton::HitTest(pos);
}

// 0x7100bd9f80
bool SelectButton::ProcessOn() {
    bool handled = true;
    switch (mState) {
    case kOff:
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        handled = true;
        break;
    case kStartDown:
    case kCancel:
        handled = false;
        break;
    default:
        break;
    }
    return handled;
}

// 0x7100bd9ff4
bool SelectButton::ProcessOff() {
    if (mState == kStartOn) {
        StartOff();
        changeState(kStartOff);
    } else if (mState == kOn) {
        StartOff();
        changeState(kStartOff);
    }
    return true;
}

// 0x7100bda08c
bool SelectButton::ProcessCancel() {
    switch (mState) {
    case kOff:
        return true;
    case kStartOn:
        return true;
    case kStartOff:
        return true;
    case kOn:
        return true;
    case kStartDown:
        return false;
    case kDown:
        StartCancel();
        changeState(kCancel);
        return true;
    case kCancel:
        return true;
    default:
        return true;
    }
}

// 0x7100bda078
bool SelectButton::UpdateCancel() {
    return mAnimators->mCurrent->mFlags & 1;
}

// 0x7100bda04c
void SelectButton::StartCancel() {
    mAnimators->select(6)->Play(Animator::PlayType(0), 1.0f);
}

// 0x7100bda0ec
void SelectButton::FinishDown() {
    changeState(kDown);
}

// 0x7100bda0fc
void SelectButton::FinishCancel() {
    selectStateAnim(0)->StopAtMin();
    changeState(kOff);
}

}  // namespace eui
