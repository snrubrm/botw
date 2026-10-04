#include "Game/UI/uiScreens.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ui {

// 0x7100a486a8 (primary); secondary RxOnly thunk0x7100a48728.
int ScreenEx::handleMessage(const ksys::Message& message) {
    switch (message.getBrokerId()) {
    case 2:
    case 3:
    case 4:
        message.getType();
        return m142(message);
    case u32(-1):
        return m141(message);
    default:
        return 0;
    }
}

// 0x7100a48c68
void ScreenEx::m144(void* a1) {
    m131(a1);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m95(a1);
    }
}

// 0x7100a48d0c
void ScreenEx::m145(void* a1) {
    m132(a1);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m96(a1);
    }
}

// 0x7100a48db0
void ScreenEx::m146(void* a1, void* a2) {
    m133(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m97(a1, a2);
    }
}

// 0x7100a48e5c
void ScreenEx::m147(void* a1, void* a2) {
    m134(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m98(a1, a2);
    }
}

// 0x7100a48f08
void ScreenEx::m148(void* a1, void* a2) {
    m135(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m99(a1, a2);
    }
}

// 0x7100a48fb4
void ScreenEx::m149(void* a1, void* a2) {
    m136(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m100(a1, a2);
    }
}

// 0x7100a49060
void ScreenEx::m150(void* a1, void* a2) {
    m137(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m101(a1, a2);
    }
}

// 0x7100a4910c
void ScreenEx::m151(void* a1, void* a2) {
    m138(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m102(a1, a2);
    }
}

// 0x7100a491b8
void ScreenEx::m152(void* a1, void* a2) {
    m139(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m103(a1, a2);
    }
}

// 0x7100a49264
void ScreenEx::m153(void* a1, void* a2) {
    m140(a1, a2);
    for (auto it = mChildren.begin(), end = mChildren.end(); it != end; ++it) {
        ScreenChild* child = it.operator->();
        auto* type = ScreenChildEx::GetRuntimeTypeInfoStatic();
        ScreenChildEx* c = child->GetRuntimeTypeInfo()->IsDerivedFrom(type) ? static_cast<ScreenChildEx*>(child) : nullptr;
        if (c)
            c->m104(a1, a2);
    }
}

// 0x7100a497b0
void ScreenEx::doButtonOnStart_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939EF8(b);
            m146(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 1);
}

// 0x7100a49888
void ScreenEx::doButtonOnEnd_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F04(b);
            m147(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 2);
}

// 0x7100a49960
void ScreenEx::doButtonOffStart_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F10(b);
            m148(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 3);
}

// 0x7100a49a38
void ScreenEx::doButtonOffEnd_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F1C(b);
            m149(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 4);
}

// 0x7100a49b10
void ScreenEx::doButtonDownStart_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F28(b);
            m150(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 5);
}

// 0x7100a49be8
void ScreenEx::doButtonDownEnd_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F34(b);
            m151(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 6);
}

// 0x7100a49cc0
void ScreenEx::doButtonCancelStart_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F40(b);
            m152(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 7);
}

// 0x7100a49d98
void ScreenEx::doButtonCancelEnd_(eui::AnimButton* button) {
    const s32 index = mButtons.indexOf(button);
    if (index >= 0) {
        auto* unit = mButtonUnits.at(index);
        auto* b = mButtons.at(index);
        if (unit && b) {
            unit->sub_7100939F4C(b);
            m153(unit, b);
        }
    }
    if (mButtonEvents)
        mButtonEvents->push(button, 8);
}

// 0x7100a487a8
void ScreenEx::m112(sead::Heap* heap) {
    s32 num_buttons = 0;
    for (eui::ListNode* node = mButtonGroup->mButtons.next; node != &mButtonGroup->mButtons; node = node->next)
        ++num_buttons;
    if (num_buttons <= 0)
        return;

    auto* queue = new (heap, 8) ButtonEventQueue;
    if (queue) {
        queue->init(heap, num_buttons * 2);
        mControls.linkNext(&queue->_8);
        mButtonEvents = queue;
    }
}

// 0x7100a49704
eui::UIController* ScreenEx::doCreateUIController_(sead::Heap* heap) {
    auto* controller = Screen::doCreateUIController_(heap);
    if (controller) {
        controller->copyRepeatSetting(Manager::instance()->_649f0);
        Manager::instance()->sub_7100A702E8(controller);
    }
    return controller;
}

// 0x7100a49758
void ScreenEx::registerController_() {
    if (isEnableControl())
        mUIController->registerWith(Manager::instance()->_649f0, false);
}

}  // namespace uking::ui
