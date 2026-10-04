#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd8670
CheckKeepButton::CheckKeepButton(const CheckKeepButton& other, LayoutEx* layout, sead::Heap* heap)
    : CheckButton(other, layout, heap) {}

// 0x7100bd86f8
void CheckKeepButton::StartDown() {
    AnimButton::StartDown();
    if (mToggleable && !mChecked && !IsPlayDisableAnim()) {
        if (mCheckAnim)
            mCheckAnim->Play(Animator::PlayType(0), 1.0f);
        mChecked = true;
    }
}

// 0x7100bd86a0
void CheckKeepButton::Uncheck() {
    if (mToggleable && mChecked && !IsPlayDisableAnim()) {
        if (mCheckAnim)
            mCheckAnim->Play(Animator::PlayType(0), -1.0f);
        mChecked = false;
    }
}

}  // namespace eui
