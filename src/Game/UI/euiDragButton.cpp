#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bd8eb4
DragButton::DragButton() {
    mFlags |= 0x400;
}

// 0x7100bd8f00
void DragButton::Build(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    AnimButton::Build(src, layout);
    mFlags &= ~0x2000;
    mPane = layout->GetPane();
}

// 0x7100bd8f3c
void DragButton::StartDrag(const sead::Vector2f& pos) {
    mStartPos = pos;
    const auto& position = mPane->GetPosition();
    mPanePos = {position.x, position.y};
}

// 0x7100bd8f5c
void DragButton::UpdateDrag(const sead::Vector2f* pos) {
    if (!pos)
        return;
    f32 x = mPanePos.x;
    if (mAllowX)
        x += pos->x - mStartPos.x;
    f32 y = mPanePos.y;
    if (mAllowY)
        y += pos->y - mStartPos.y;
    mPane->SetPosition(nn::util::Float2{x, y});
}

// 0x7100bd8fb0
void DragButton::FinishDrag(const sead::Vector2f* pos) {
    if (mFlags & 0x40)
        Off();
    else
        Cancel();
}

// 0x7100bd8fcc
void DragButton::BuildStateAnim(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    const char* names[8] = {
        src.FindFunctionalAnimName("On"),     src.FindFunctionalAnimName("TouchOn"),
        src.FindFunctionalAnimName("Off"),    src.FindFunctionalAnimName("TouchOff"),
        src.FindFunctionalAnimName("Decide"), src.FindFunctionalAnimName("TouchDecide"),
        src.FindFunctionalAnimName("Cancel"), src.FindFunctionalAnimName("TouchCancel"),
    };
    mAnimators = layout->createAnimatorSet(names, 8, true);
}

// 0x7100bd90b8
void DragButton::StartCancel() {
    selectStateAnim(6)->Play(Animator::PlayType(0), 1.0f);
}

// 0x7100bd90e0
void DragButton::FinishCancel() {
    const u16 flags = mFlags;
    Animator* anim = selectStateAnim(0);
    if (!(flags & 0x40)) {
        anim->StopAtMax();
        changeState(kOn);
    } else {
        anim->StopAtMin();
        changeState(kOff);
    }
}

}  // namespace eui
