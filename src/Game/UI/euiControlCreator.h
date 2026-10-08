#pragma once

#include <nn/ui2d/Layout.h>
#include "Game/UI/euiControlBase.h"

namespace eui {
class ButtonBase;
class ButtonGroup;
class LayoutEx;

// Vtable 0x71024c7310 extends the SDK creator's destructor pair/CreateControl slot.
// Constructor 0x7100bd8808 stores the button group and two owner list roots.
class ControlCreator : public nn::ui2d::ControlCreator {
public:
    ControlCreator(ButtonGroup* buttons, ListNode* controls, ListNode* children);
    ~ControlCreator() override;
    void CreateControl(nn::gfx::Device*, nn::ui2d::Layout* layout,
                       const nn::ui2d::ControlSrc& src) override;
    virtual ControlBase* createControl(const nn::ui2d::ControlSrc& src, LayoutEx* layout);
    virtual void registerButton(ButtonBase* button);

protected:
    /* 0x08 */ ButtonGroup* mButtons;
    /* 0x10 */ ListNode* mControls;
    /* 0x18 */ ListNode* mChildren;
};
static_assert(sizeof(ControlCreator) == 0x20);
}  // namespace eui
