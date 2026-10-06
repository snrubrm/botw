#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a41558
void ScreenRupee::sub_7100A41558() {
    _3610 = true;
    if (mState == 0 || mState == 3)
        sub_7100A410D8(1);
}

// 0x7100a20dd0
bool ScreenMainShortCut::sub_7100A20DD0() {
    if (isSameStateId(*mStateMachine.getState(), sUnk_71025ef170))
        return false;
    return !isSameStateId(*mStateMachine.getState(), sUnk_71025ef290);
}

// 0x71009fd674
bool ScreenAppTool::sub_71009FD674() {
    return isSameStateId(*mStateMachine.getState(), sUnk_71025ec670);
}

// 0x7100a31be0
void ScreenPauseMenuInfo::sub_7100A31BE0() {
    if (_3904 == 1)
        _3904 = 2;
    if (_391c == 1)
        _391c = 2;
}

// 0x7100a1ab58
void ScreenMainScreen::sub_7100A1AB58(s32 a1) {
    if (_3658)
        _3658->_150 = a1;
}

// 0x7100a1e1e0
bool ScreenMainScreen::sub_7100A1E1E0() {
    if (!_3ca8)
        return false;
    return !_3ca8->isAnimOpenEnd(false);
}

}  // namespace uking::ui

namespace uking::ui {

// 0x71010b343c
bool ScreenMessageDialog::sub_71010B343C() {
    switch (_350) {
    case 6:
    case 7:
    case 10:
        return true;
    default:
        return false;
    }
}

// 0x71010b34b4
void ScreenMessageDialog::sub_71010B34B4(bool choice_mode, s32 stock) {
    if (choice_mode) {
        _738 = stock;
        _73c = 1;
    } else {
        _738 = -1;
        _73c = -1;
    }
}

// 0x71010b34a0
void ScreenMessageDialog::sub_71010B34A0(bool a1) {
    _773 = a1 ? 1 : 2;
}

// 0x71010b34d0
const char* ScreenMessageDialog::getLayoutName_() const {
    return !_76a ? "Message_00" : "MessageSp_00";
}

// 0x710109e94c
void ScreenDemoMessage::sub_710109E94C() {
    if (_548 != -1)
        close(-1);
}

// 0x710109e96c
void ScreenDemoMessage::sub_710109E96C() {
    _548 = -1;
}

// 0x710109e978
void ScreenDemoMessage::sub_710109E978() {
    _558 = true;
}

// 0x710109e9d4 (CSV unnamed; slot 27)
eui::TagProcessor* ScreenDemoMessage::doCreateTagProcessor_(sead::Heap* heap) {
    auto* processor = ScreenBase::doCreateTagProcessor_(heap);
    processor->setRubyEnabled(true);
    return processor;
}

// 0x710109e984 (slot 93)
void ScreenDemoMessage::m93(sead::Heap*) {
    _550 = mLayout->tryCreateAnimatorAutoWithWarning("Pos", true);
    if (_550)
        _550->Stop(0.0f);
}

// 0x710109e9f0 (slot 94)
void ScreenDemoMessage::m94() {
    if (_558) {
        _548 = 0;
        if (_300.getString()) {
            bool has_next_page = false;
            mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, 0, true,
                                                       nullptr);
            x_2();
            _548 = has_next_page ? _548 + 1 : -1;
        }
        _558 = false;
    }
}

// 0x710109ea70 (slot 98)
void ScreenDemoMessage::m98() {
    if (_300.getString()) {
        bool has_next_page = false;
        mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, _548, true,
                                                   nullptr);
        x_2();
        _548 = has_next_page ? _548 + 1 : -1;
    }
    if (_550)
        _550->Stop(_559 ? 1.0f : 0.0f);
}

// 0x710109eb08 (slot 101)
void ScreenDemoMessage::m101() {
    if (_548 != -1)
        open(1);
}

// 0x71010a87f0
// NON_MATCHING: the original keeps the "type 18 while 19 is current" case as its own branch that jumps to the shared
// store; clang makes it a select
bool ScreenMessageTips::sub_71010A87F0(s32 type) {
    if ((type | 1) != 19)
        return false;

    if (type == 18 && _3a8 == 19)
        type = 19;
    if (_3a8 == type)
        _3ac = type;
    else
        type = _3ac;
    return type != 29;
}

// 0x7100a00e74
void ScreenChangeController::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Type", false);
}

// 0x7100a00ea8
void ScreenChangeController::m94() {
    if (isOpened())
        close(-4);
}

// 0x7100a041b4
void ScreenDemoStart::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Decide", false);
}

// 0x7100a0e870
void ScreenKeyNum::m93(sead::Heap*) {
    _3618 = mLayout->createAnimatorAuto("Flash", false);
}

// 0x71009fb988
void ScreenAppSystemWindowNoBtn::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("FadeOut", false);
}

// 0x7100a321e8
void ScreenPauseMenuMantan::m93(sead::Heap*) {
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next)
        static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node))->mFlags |= 0x20;
    mButtonGroup->_38 &= ~2;
}

// 0x7100a2c1ac
void ScreenPauseMenuEiketsu::m93(sead::Heap*) {
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next)
        static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node))->mFlags |= 0x20;
    mButtonGroup->_38 &= ~2;
}

// 0x7100a2be98
void ScreenPauseMenuBG::m93(sead::Heap*) {
    mLayout->startAnimCloseImpl_(false, true);
}

// 0x7100a2bec8
void ScreenPauseMenuBG::m94() {
    if (_3610)
        x_2();
}

// 0x7100a0dfc8
void ScreenHomeMenuCapture::m93(sead::Heap*) {
    _3610 = sub_7100BEAFB0("Pa_LoadingIcon_00");
    if (_3610)
        _3610->startAnimCloseImpl_(false, true);
}

// 0x7100a0e00c
void ScreenHomeMenuCapture::m94() {
    if (!_3610)
        return;
    if (_3618) {
        if (_3610->_91 == 0)
            _3610->sub_7100BDDE7C(false, 0, true);
    } else if (_3610->_91 == 2) {
        _3610->startAnimCloseImpl_(false, false);
    }
}

// 0x7100a4de00
void ScreenShopBtnList5::m94() {
    x_2();
}

// 0x7100a4ca64
void ScreenShopBtnList20::m102(eui::AnimButton*) {
    _3868 = 0;
}

// 0x7100a502e4
void ScreenShopHorse::m99() {
    _36bc = 0;
}

// 0x7100a2c28c
void ScreenPauseMenuEiketsu::m101() {
    _292 |= 0x20;
}

// 0x71009fc9e0
void ScreenAppSystemWindow::m101() {
    _3610 = 10;
}

// 0x7100a2807c
void ScreenMiniGame::m100() {
    _3650 = 0;
}

// 0x71009fc9ec
void ScreenAppSystemWindow::m106(eui::AnimButton* button) {
    if (!button->IsPlayDisableAnim())
        mButtonGroup->_38 &= ~2;
}

// 0x7100a060ac
void ScreenDLCWindow::m106(eui::AnimButton* button) {
    mButtonGroup->_38 &= ~2;
    if (button->mTag == 89)
        invokeSoundLink2Event_("mc_WindowClose");
}

// 0x7100a205fc
void ScreenMainShortCut::m99() {
    if (sub_7100AA948C())
        mStateMachine.changeState(&sUnk_71025ef170);
    else
        mStateMachine.changeState(&sUnk_71025ef290);
}

// 0x7100a0e054
void ScreenHomeMenuCapture::m98() {
    x_2();
    _3618 = 0;
    if (_3610)
        _3610->startAnimCloseImpl_(false, true);
}

// 0x7100a60678
void ScreenSystemWindowNoBtn::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("FadeOut", false);
    _3618 = mLayout->createAnimatorAuto("Type", false);
}

// 0x7100a286bc
void ScreenOPtext::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Type", true);
    if (_3610)
        _3610->Stop(_3618);
}

// 0x7100a4a9c4
void ScreenSeekPadMenuBG::m93(sead::Heap*) {
    mLayout->startAnimCloseImpl_(false, true);
    _3610 = mLayout->tryCreateAnimatorAuto("Type", false);
    if (_3610)
        _3610->StopAtMax();
}

// 0x7100a4dd8c
void ScreenShopBtnList5::m93(sead::Heap*) {
    _3618 = mLayout->createAnimatorAuto("Type", true);
    if (_3618)
        _3618->StopAtMin();
    _3620 = mLayout->createAnimatorAuto("HaveNumOff", true);
    if (_3620)
        _3620->StopAtMin();
}

// 0x7100a00948
void ScreenChallengeWin::m93(sead::Heap*) {
    _3610 = sub_7100BEAFB0("Pa_ChallengeWin_00");
    if (!_3610)
        return;
    _3868 = _3610->tryCreateAnimatorAuto("Check", false);
    if (_3868)
        _3868->StopAtMin();
    _3870 = _3610->createAnimatorAuto("GuideOff", false);
    if (_3870)
        _3870->StopAtMin();
}

// 0x7100a00440
void ScreenBootUp::m94() {
    if (isOpened()) {
        if (mLayout->mPane)
            mLayout->mPane->SetVisible(false);
        close(-4);
    }
}

// 0x7100a40c58
void ScreenReadyGo::m94() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    if (animator && animator->mFrame == static_cast<f32>(animator->GetFrameSize()))
        close(-4);
}

// 0x71009fb9bc
void ScreenAppSystemWindowNoBtn::m94() {
    if ((_291 & 2) || isOpened() ||
        (_3610 && _3610->mFrame == static_cast<f32>(_3610->GetFrameSize())))
        _292 |= 0x20;
}

// 0x7100a606c4
void ScreenSystemWindowNoBtn::m94() {
    if ((_291 & 2) || isOpened() ||
        (_3610 && _3610->mFrame == static_cast<f32>(_3610->GetFrameSize())))
        _292 |= 0x20;
}

}  // namespace uking::ui
