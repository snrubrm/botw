#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include <nn/ui2d/Pane.h>

namespace eui {

// 0x7100bd7b74
ButtonGroup::ButtonGroup() = default;


// 0x7100bd81d0
ButtonBase* ButtonGroup::FindControlByName(const char* name) {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        auto* control = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        if (IsNameEqual(name, control->mName))
            return control;
    }
    return nullptr;
}

// 0x7100bd822c
ButtonBase* ButtonGroup::FindButton(const char* name, const char* layout_name) {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        auto* button = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        LayoutEx* layout = (button->mFlags & 0x2000) ? button->mLayout->_88 : button->mLayout;
        if (IsNameEqual(name, button->mName) && layout && IsNameEqual(layout_name, layout->mPane->GetName()))
            return button;
    }
    return nullptr;
}

// 0x7100bd82c8
ButtonBase* ButtonGroup::FindButton(const char* name, LayoutEx* layout) {
    for (ListNode* node = mButtons.next; node != &mButtons; node = node->next) {
        auto* button = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        LayoutEx* button_layout = (button->mFlags & 0x2000) ? button->mLayout->_88 : button->mLayout;
        if (IsNameEqual(name, button->mName) && button_layout == layout)
            return button;
    }
    return nullptr;
}

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
