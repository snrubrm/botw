#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bd8428
CheckButton::CheckButton(const CheckButton& other, LayoutEx* layout, sead::Heap* heap)
    : mChecked(other.mChecked), mCheckAnim(nullptr) {
    CloneImpl_(other, layout, heap);
    mCheckAnim = layout->tryCreateAnimatorAutoWithWarning(other.mCheckAnim->mName, true);
    mCheckAnim->mFlags |= 0x10;
    mCheckAnim->mFlags &= ~0x20;
}

// 0x7100bd84c4
void CheckButton::Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    AnimButton::Build(src, layout);
    mCheckAnim = layout->tryCreateAnimatorAutoWithWarning(src.FindFunctionalAnimName("Check"), true);
    mCheckAnim->mFlags |= 0x10;
    mCheckAnim->mFlags &= ~0x20;
}

// 0x7100bd8538
void CheckButton::StartDown() {
    AnimButton::StartDown();
    if (mToggleable) {
        if (!IsPlayDisableAnim()) {
            if (mCheckAnim)
                mCheckAnim->Play(Animator::PlayType(0), mChecked ? -1.0f : 1.0f);
            mChecked = !mChecked;
        }
    }
}

// 0x7100bd85ac
bool CheckButton::UpdateDown() {
    bool done = AnimButton::UpdateDown();
    if (mToggleable && mCheckAnim && !IsPlayDisableAnim()) {
        if (mChecked)
            done = done && mCheckAnim->mFrame == f32(mCheckAnim->GetFrameSize());
        else
            done = done && mCheckAnim->mFrame == 0.0f;
    }
    return done;
}

}  // namespace eui
