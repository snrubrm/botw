#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiBoundingEx.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include <nn/font/font_Util.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/ResExtUserData.h>

namespace eui {

// 0x7100befe9c / 0x7100bf01dc: the library's font type test. The original's out-of-line copy sits
// between this TU's button helpers, and the callers only declare it.
bool sub_7100BF00BC(nn::ui2d::Pane* pane);

// 0x7100bf01dc
void TapButton::CreateTapButton(nn::ui2d::Pane* pane, LayoutEx* layout, ButtonGroup* group) {
    if (!sub_7100BF00BC(pane))
        return;
    const auto* data = pane->FindExtUserDataByName("TapButtonAnim");
    if (!data)
        return;
    auto* animator = layout->tryCreateAnimatorAuto(data->GetString(), true);
    if (!animator)
        return;
    auto* heap = GetNwAllocatorHeap();
    auto* button = new (heap, 8) TapButton;
    button->mLayout = layout;
    button->SetTouch(layout->mScreen && layout->mScreen->_104);
    button->mHitPane = pane;
    button->mAnimators = new (heap, 8) AnimatorSet;
    button->mAnimators->allocBuffer(6, heap);
    animator->mFlags = (animator->mFlags & ~0x30) | 0x10;
    button->mAnimators->setAnimator(4, animator);
    button->mName = pane->GetName();
    button->mFlags |= 0x200;
    group->mButtons.linkPrev(&button->_8);
}

// 0x7100bf0324 / 0x7100bf0328
void TapButton::On() {}
void TapButton::Off() {}

// 0x7100bf032c
bool TapButton::ProcessDown() {
    switch (mState) {
    case kOff:
        StartDown();
        changeState(kStartDown);
        return false;
    case kStartOn:
        return false;
    case kStartOff:
        return false;
    case kOn:
        return false;
    case kStartDown:
        return true;
    case kDown:
        return true;
    case kCancel:
        return false;
    default:
        return true;
    }
}

// 0x7100bf039c
void TapButton::FinishDown() {
    changeState(kDown);
    changeState(kOff);
}

// 0x7100bf03d8
void TapButton::ForceOff() {
    ButtonBase::ForceOff();
    selectStateAnim(4)->StopAtMin();
}

}  // namespace eui
