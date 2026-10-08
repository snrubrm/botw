#include "Game/UI/euiControlCreator.h"
#include <cstring>
#include <new>
#include <nn/ui2d/ControlSrc.h>
#include "Game/UI/euiButton.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTraceGaugeControl.h"

namespace eui {
// 0x7100bd8808
ControlCreator::ControlCreator(ButtonGroup* buttons, ListNode* controls, ListNode* children)
    : mButtons(buttons), mControls(controls), mChildren(children) {}

// 0x7100bd8c20 / 0x7100bd8c24
ControlCreator::~ControlCreator() = default;

// 0x7100bd8820
void ControlCreator::CreateControl(nn::gfx::Device*, nn::ui2d::Layout* layout,
                                  const nn::ui2d::ControlSrc& src) {
    createControl(src, static_cast<LayoutEx*>(layout));
}

// 0x7100bd8830
// NON_MATCHING: the compiler clones null-allocation initialize paths and omits post-call null guards.
ControlBase* ControlCreator::createControl(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    const char* name = src.mClassName;
    AnimButton* button;
    if (std::strcmp("NormalButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(NormalButton), 4);
        button = memory ? new (memory) NormalButton : nullptr;
    } else if (std::strcmp("DecisionButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(DecisionButton), 4);
        button = memory ? new (memory) DecisionButton : nullptr;
    } else if (std::strcmp("SelectButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(SelectButton), 4);
        button = memory ? new (memory) SelectButton : nullptr;
    } else if (std::strcmp("CheckButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(CheckButton), 4);
        button = memory ? new (memory) CheckButton : nullptr;
    } else if (std::strcmp("DragButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(DragButton), 4);
        button = memory ? new (memory) DragButton : nullptr;
    } else if (std::strcmp("CheckKeepButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(CheckKeepButton), 4);
        button = memory ? new (memory) CheckKeepButton : nullptr;
    } else if (std::strcmp("TwoTouchCheckKeepButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(TwoTouchCheckKeepButton), 4);
        button = memory ? new (memory) TwoTouchCheckKeepButton : nullptr;
    } else if (std::strcmp("UniteButton", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(UniteButton), 4);
        button = memory ? new (memory) UniteButton : nullptr;
    } else if (std::strcmp("BoxCursor", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(BoxCursorControl), 4);
        auto* control = memory ? new (memory) BoxCursorControl : nullptr;
        control->initialize(src, layout);
        if (control)
            mControls->linkPrev(&control->_8);
        return control;
    } else if (std::strcmp("TraceGauge", name) == 0) {
        void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(TraceGaugeControl), 4);
        auto* control = memory ? new (memory) TraceGaugeControl : nullptr;
        control->initialize(src, layout);
        if (control)
            mControls->linkPrev(&control->_8);
        return control;
    } else {
        return nullptr;
    }
    button->Build(src, layout);
    if (button)
        registerButton(button);
    return button;
}

// 0x7100bd8b58
// NON_MATCHING: reverse-list traversal uses the root sentinel rather than the original iterator end.
void ControlCreator::registerButton(ButtonBase* button) {
    ListNode* previous = nullptr;
    ListNode* node = mButtons->mButtons.prev;
    while (node != &mButtons->mButtons) {
        auto* current = static_cast<ButtonBase*>(ControlBase::fromNode(node));
        if (current->mLayout->_88 != button->mLayout) {
            if (previous)
                previous->linkPrev(&button->_8);
            else
                mButtons->mButtons.linkPrev(&button->_8);
            return;
        }
        previous = node;
        node = node->prev;
    }
    mButtons->mButtons.linkNext(&button->_8);
}
}  // namespace eui
