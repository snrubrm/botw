#include "Game/UI/euiButton.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include <nn/ui2d/Pane.h>

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

// 0x7100beff6c
void HoverButton::Down() {
    if (mFlags & 0x40)
        Off();
}

}  // namespace eui
