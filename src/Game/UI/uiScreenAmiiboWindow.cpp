#include "Game/AOC/aocHardModeManager.h"
#include <algorithm>
#include <thread/seadThread.h>
#include <thread/seadDelegateThread.h>
#include <prim/seadDelegate.h>
#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/uiSwkbdMgr.h"
#include "KingSystem/Quest/qstQuest.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiMessageMgr.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiAlignPane.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiCapturePane.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Resource/resHandle.h"
#include "Game/gameGraphics.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiManager.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameRoot1.h"
#include "Game/gameRuneMgr.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiTagProcessor.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/AOC/aocManager.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/StageInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <nn/os.h>
#include "Game/gameUnkRttiPlaceholders.h"

// The ScreenAmiiboWindow functions (one TU in the original: 0x71009d06f4 - 0x71009d107c).
namespace uking::ui {

namespace {
// 0x710247f588
const sead::SafeString sAmiiboWindowMsg = "LayoutMsg/AmiiboWindow_00";
}  // namespace

// 0x71009d0898
void ScreenAmiiboWindow::sub_71009D0898(s32 text_id, s32 button_id) {
    sead::FormatFixedSafeString<64> text_label("%04d", text_id);
    sead::FormatFixedSafeString<64> button_label("%04d", button_id);
    eui::MessageString text;
    eui::MessageString button;
    getMessage(sAmiiboWindowMsg, text_label, &text);
    getMessage(sAmiiboWindowMsg, button_label, &button);
    if (_3618)
        setWidgetString(_3618, "T_Text_00", text);
    if (_3620)
        setWidgetString(_3620, "T_Btn_00", button);
    if (_3640)
        _3640->setFlag10(true);
    if (_3648)
        _3648->setFlag10(false);
    if (_3650)
        _3650->setFlag10(false);
    if (_3658)
        _3658->setFlag10(false);
}

// 0x71009d09ec
void ScreenAmiiboWindow::sub_71009D09EC(s32 text1_id, s32 text2_id, s32 button1_id, s32 button2_id,
                                        s32 button3_id) {
    sead::FormatFixedSafeString<64> text1_label("%04d", text1_id);
    sead::FormatFixedSafeString<64> text2_label("%04d", text2_id);
    sead::FormatFixedSafeString<64> button1_label("%04d", button1_id);
    sead::FormatFixedSafeString<64> button2_label("%04d", button2_id);
    sead::FormatFixedSafeString<64> button3_label("%04d", button3_id);
    eui::MessageString text1;
    eui::MessageString text2;
    eui::MessageString button1;
    eui::MessageString button2;
    eui::MessageString button3;
    getMessage(sAmiiboWindowMsg, text1_label, &text1);
    getMessage(sAmiiboWindowMsg, text2_label, &text2);
    getMessage(sAmiiboWindowMsg, button1_label, &button1);
    getMessage(sAmiiboWindowMsg, button2_label, &button2);
    getMessage(sAmiiboWindowMsg, button3_label, &button3);
    if (_3618) {
        setWidgetString(_3618, "T_Text_01", text1);
        setWidgetString(_3618, "T_Text_02", text2);
    }
    if (_3628)
        setWidgetString(_3628, "T_Btn_00", button1);
    if (_3630)
        setWidgetString(_3630, "T_Btn_00", button2);
    if (_3638)
        setWidgetString(_3638, "T_Btn_00", button3);
    if (_3640)
        _3640->setFlag10(false);
    if (_3648)
        _3648->setFlag10(false);
    if (_3650)
        _3650->setFlag10(true);
    if (_3658)
        _3658->setFlag10(true);
}

// 0x71009d06f4 (slot 154)
// NON_MATCHING: the _3660 / _3668 stores rematerialise the field load through an address phi
// (extra mov/add and a reload) where the original keeps the loaded value in a register.
void ScreenAmiiboWindow::m154(s32 type, bool flag) {
    _3614 = type;
    _368a = flag;
    _368b = ksys::gdt::getFlag_AmiiboItemOnOff(false);
    switch (_3614) {
    case 0:
        sub_71009D0898(4, 0);
        if (_3670)
            _3670->Stop(0.0f);
        if (_3678)
            _3678->StopAtMin();
        if (_3680)
            _3680->Stop(0.0f);
        _3660 = _3640;
        _3668 = _3640;
        break;
    case 1:
        sub_71009D09EC(5, 7, 0, 1, 2);
        if (_3670)
            _3670->Stop(1.0f);
        if (_3678)
            _3678->StopAtMin();
        if (_3680)
            _3680->Stop(1.0f);
        _3660 = _3658;
        _3668 = _3650;
        break;
    case 2:
        sub_71009D09EC(6, 8, 0, 1, 3);
        if (_3670)
            _3670->Stop(1.0f);
        if (_3678)
            _3678->StopAtMin();
        if (_3680)
            _3680->Stop(0.0f);
        _3660 = _3658;
        _3668 = _3650;
        break;
    default:
        return;
    }
    open(1);
}

// 0x71009d0c84
void ScreenAmiiboWindow::m93(sead::Heap*) {
    _3618 = mLayout;
    _3620 = sub_7100BEAFB0("Pa_BtnC_00");
    _3628 = sub_7100BEAFB0("Pa_BtnC_01");
    _3630 = sub_7100BEAFB0("Pa_BtnL_00");
    _3638 = sub_7100BEAFB0("Pa_BtnR_00");
    _3640 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnC_00"));
    _3648 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnC_01"));
    _3650 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnL_00"));
    _3658 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnR_00"));
    _3670 = mLayout->tryCreateAnimatorAuto("Type", true);
    _3678 = mLayout->tryCreateAnimatorAuto("ToCheck", true);
    _3680 = mLayout->tryCreateAnimatorAuto("Illust", true);
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next)
        static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node))->mFlags |= 0x20;
}

// 0x71009d0ee4
void ScreenAmiiboWindow::m98() {
    _3610 = 4;
    x_2();
    registerController_();
    mButtonGroup->_38 &= ~2;
}

// 0x71009d0f2c
void ScreenAmiiboWindow::m99() {
    if (_3689) {
        if (_3668)
            _3668->DownOff(false);
    } else if (_3688) {
        if (_3660)
            _3660->DownOff(false);
    } else {
        mButtonGroup->_38 |= 2;
    }
}

// 0x71009d0f78
void ScreenAmiiboWindow::m100() {
    if (_368a && (ksys::gdt::getFlag_AmiiboItemOnOff(false) & 1) != _368b)
        SaveSystem::instance()->sub_71009145F8();
}

// 0x71009d0fd4
void ScreenAmiiboWindow::m101() {
    _3614 = 3;
    _368a = 0;
    _3668 = nullptr;
    _3660 = nullptr;
    sub_7100AA8784();
}

// 0x71009d0ff0
void ScreenAmiiboWindow::m106(eui::AnimButton* button) {
    if (_3658 == button) {
        if (_3678)
            _3678->PlayAuto(1.0f);
        if (_3650)
            _3650->setFlag10(false);
        if (_3658)
            _3658->setFlag10(false);
        _3688 = 0;
        _3689 = 0;
    } else {
        mButtonGroup->_38 &= ~2;
    }
}

// 0x71009d107c
void ScreenAmiiboWindow::m107(eui::AnimButton* button) {
    if (_3640 == button || _3648 == button) {
        _3610 = 2;
    } else if (_3650 == button) {
        _3610 = 1;
    } else if (_3658 == button) {
        switch (_3614) {
        case 1:
            ksys::gdt::setFlag_AmiiboItemOnOff(true);
            break;
        case 2:
            ksys::gdt::setFlag_AmiiboItemOnOff(false);
            break;
        }
    }
    if (_3658 != button)
        close(-1);
}

}  // namespace uking::ui
