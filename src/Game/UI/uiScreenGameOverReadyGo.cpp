#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// 0x7100a0a538
void ScreenGameOver::m93(sead::Heap*) {
    _3618 = mLayout->createAnimatorAuto("Color", false);
    _3620 = findPane_("P_BG_00");
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next) {
        auto* button = static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node));
        button->mFlags |= 0x20;
        button->setFlag10(false);
    }
    getStateMachine().startState(&sUnk_710261ee98);
}

// 0x7100a0a5ec
void ScreenGameOver::m94() {
    getStateMachine().run();
}

// 0x7100a0a71c
void ScreenGameOver::m99() {
    moveBoxCursorByTag_(120);
    getStateMachine().changeState(&sUnk_71025edda0);
}

// 0x7100a0a74c
void ScreenGameOver::m100() {
    getStateMachine().changeState(&sUnk_710261ee98);
}

// 0x7100a0a934
void ScreenGameOver::m154() {
    if (_3610)
        return;
    if (auto* button = mButtonGroup->FindButtonByTag(120))
        button->setFlag10(true);
    if (auto* button = mButtonGroup->FindButtonByTag(121))
        button->setFlag10(true);
}

// 0x7100a0a834
void ScreenGameOver::m106(eui::AnimButton* button) {
    switch (button->mTag) {
    case 120:
        _3614 = 7;
        _3610 = 1;
        if (auto* b = mButtonGroup->FindButtonByTag(120))
            b->setFlag10(false);
        if (auto* b = mButtonGroup->FindButtonByTag(121))
            b->setFlag10(false);
        break;
    case 121:
        getStateMachine().changeState(&sUnk_71025ede00);
        break;
    }
}

// 0x7100a0aa18
void ScreenGameOver::m158() {
    createAndLoadScreenIfNeededImpl(ScreenId::SystemWindow00, nullptr);
    auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (screen)
        screen->m154(1, mDrawTarget, nullptr);
}

// 0x7100a0aaec
void ScreenGameOver::m159() {
    switch (sub_7100A64304()) {
    case 0:
        _3610 = 1;
        _3614 = 6;
        getStateMachine().changeState(&sUnk_71025edda0);
        break;
    case 1:
        moveBoxCursorByTag_(121);
        getStateMachine().changeState(&sUnk_71025edda0);
        break;
    }
}

// 0x7100a0a75c
void ScreenGameOver::m101() {
    _3610 = 0;
    _3614 = 7;
}

// 0x7100a0a8d8
bool ScreenGameOver::sub_7100A0A8D8() {
    if (isOpening())
        return false;
    Screen::close(-1);
    return true;
}

// 0x7100a0a914
bool ScreenGameOver::sub_7100A0A914() {
    return !_3620 || _3620->GetAlpha() == 255;
}

// 0x7100a0a9a8
void ScreenGameOver::m156() {
    if (_3610)
        return;
    if (auto* button = mButtonGroup->FindButtonByTag(120))
        button->setFlag10(false);
    if (auto* button = mButtonGroup->FindButtonByTag(121))
        button->setFlag10(false);
}

// 0x7100a40bf8
bool ScreenReadyGo::sub_7100A40BF8() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    return animator && animator->mFrame >= 90.0f;
}

}  // namespace uking::ui
