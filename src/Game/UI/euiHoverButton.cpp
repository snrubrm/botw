#include "Game/UI/euiButton.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/ResExtUserData.h>

namespace eui {

// 0x7100befdc4
void HoverButton::Initialize(sead::Heap* heap, nn::ui2d::Pane* pane, Animator* anim,
                             LayoutEx* layout) {
    mLayout = layout;
    SetTouch(layout->mScreen && layout->mScreen->_104);
    mFlags &= ~0x2000;
    mHitPane = pane;
    mAnimators = new (heap, 8) AnimatorSet;
    mAnimators->allocBuffer(4, heap);
    anim->mFlags = (anim->mFlags & ~0x30) | 0x10;
    mAnimators->setAnimator(0, anim);
    mName = pane->GetName();
    mFlags |= 0x100;
}

// Declaration-only: the complete native guard and both hover/tap factory callers
// establish bool(Pane*). Its RTTI target25D2960 owner remains unmodeled.
bool sub_7100BF00BC(nn::ui2d::Pane* pane);

// 0x7100befe9c
void sub_7100BEFE9C(nn::ui2d::Pane* pane, LayoutEx* layout, ButtonGroup* group) {
    if (!sub_7100BF00BC(pane))
        return;
    const auto* data = pane->FindExtUserDataByName("HoverButtonAnim");
    if (!data)
        return;
    auto* animator = layout->tryCreateAnimatorAuto(data->GetString(), true);
    if (!animator)
        return;
    auto* heap = GetNwAllocatorHeap();
    auto* button = new (heap, 8) HoverButton;
    button->Initialize(heap, pane, animator, layout);
    group->mButtons.linkPrev(&button->_8);
}

// 0x7100beff6c
void HoverButton::Down() {
    if (mFlags & 0x40)
        Off();
}

}  // namespace eui
