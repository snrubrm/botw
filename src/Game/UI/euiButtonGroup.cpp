#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd7b74
ButtonGroup::ButtonGroup() = default;

// 0x7100bd8378
bool ButtonGroup::IsExistExcludingDown() const {
    if (!(_38 & 1))
        return false;
    for (const ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        const auto* button = static_cast<const ButtonBase*>(ControlBase::fromNode(node));
        if ((button->mFlags & 0x20) && button->IsDowning())
            return true;
    }
    return false;
}

// 0x7100bd817c
ButtonBase* ButtonGroup::FindDownButton() {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        auto* button = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        if (button->IsDowning())
            return button;
    }
    return nullptr;
}

// 0x7100bd8338
ButtonBase* ButtonGroup::FindButtonByTag(s32 tag) {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        auto* button = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        if (button->mTag == tag)
            return button;
    }
    return nullptr;
}

// 0x7100bd83d8
void ButtonGroup::sub_7100BD83D8() {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next)
        static_cast<ButtonBase*>(ControlBase::fromNode(node))->ForceOff();
}

// 0x7100bd8118
void ButtonGroup::SetTouchDevice(bool touch) {
    _38 = touch ? (_38 | 4) : (_38 & ~4);
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next)
        static_cast<AnimButton*>(ControlBase::fromNode(node))->SetTouch(touch);
}

}  // namespace eui
