#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiUtils.h"
#include "Game/AOC/aocHardModeManager.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/System/PlayReportMgr.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a0d770), merged into the block at 0x71025eea50 after the
// uiTUStatics.h objects; the message strings start at +0x148.
static sead::SafeString sHardMode = "StaticMsg/HardMode";
static sead::SafeString sSystemWindow = "LayoutMsg/SystemWindow_00";
static sead::SafeString sZero = "0000";
static sead::SafeString sOne = "0001";
static sead::SafeString sTwo = "0002";
static sead::SafeString sFive = "0005";
static sead::SafeString sThree = "0003";
static sead::SafeString sThirteen = "0013";
static sead::SafeString sFourteen = "0014";

ksys::StateTemplate<ScreenHardMode> sUnk_71025ee1b0(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_NoNormalSave_NoHardSave_00", &ScreenHardMode::m154, &ScreenHardMode::m155,
    &ScreenHardMode::m156, &ScreenHardMode::m157, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee210(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_NoNormalSave_YesHardSave_00", &ScreenHardMode::m158, &ScreenHardMode::m159,
    &ScreenHardMode::m160, &ScreenHardMode::m161, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee270(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_YesNormalSave_NoHardSave_00", &ScreenHardMode::m162, &ScreenHardMode::m163,
    &ScreenHardMode::m164, &ScreenHardMode::m165, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee2d0(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_YesNormalSave_NoHardSave_01", &ScreenHardMode::m166, &ScreenHardMode::m167,
    &ScreenHardMode::m168, &ScreenHardMode::m169, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee330(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_YesNormalSave_NoHardSave_02", &ScreenHardMode::m170, &ScreenHardMode::m171,
    &ScreenHardMode::m172, &ScreenHardMode::m173, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee390(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_YesNormalSave_YesHardSave_00", &ScreenHardMode::m174, &ScreenHardMode::m175,
    &ScreenHardMode::m176, &ScreenHardMode::m177, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee3f0(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromNormal_YesNormalSave_YesHardSave_01", &ScreenHardMode::m178, &ScreenHardMode::m179,
    &ScreenHardMode::m180, &ScreenHardMode::m181, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee450(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_NoNormalSave_NoHardSave_00", &ScreenHardMode::m182, &ScreenHardMode::m183,
    &ScreenHardMode::m184, &ScreenHardMode::m185, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee4b0(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_YesNormalSave_NoHardSave_00", &ScreenHardMode::m186, &ScreenHardMode::m187,
    &ScreenHardMode::m188, &ScreenHardMode::m189, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee510(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_NoNormalSave_YesHardSave_00", &ScreenHardMode::m190, &ScreenHardMode::m191,
    &ScreenHardMode::m192, &ScreenHardMode::m193, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee570(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_NoNormalSave_YesHardSave_01", &ScreenHardMode::m194, &ScreenHardMode::m195,
    &ScreenHardMode::m196, &ScreenHardMode::m197, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee5d0(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_NoNormalSave_YesHardSave_02", &ScreenHardMode::m198, &ScreenHardMode::m199,
    &ScreenHardMode::m200, &ScreenHardMode::m201, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee630(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_YesNormalSave_YesHardSave_00", &ScreenHardMode::m202, &ScreenHardMode::m203,
    &ScreenHardMode::m204, &ScreenHardMode::m205, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee690(
    ++ksys::sUnk_71025cb4c8, "::StateID_FromHard_YesNormalSave_YesHardSave_01", &ScreenHardMode::m206, &ScreenHardMode::m207,
    &ScreenHardMode::m208, &ScreenHardMode::m209, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee6f0(
    ++ksys::sUnk_71025cb4c8, "::StateID_AutoSaveErase_00", &ScreenHardMode::m210, &ScreenHardMode::m211,
    &ScreenHardMode::m212, &ScreenHardMode::m213, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee750(
    ++ksys::sUnk_71025cb4c8, "::StateID_ReserveSaveDataForHardMode_00", &ScreenHardMode::m214, &ScreenHardMode::m215,
    &ScreenHardMode::m216, &ScreenHardMode::m217, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee7b0(
    ++ksys::sUnk_71025cb4c8, "::StateID_NoAoC_HardModeSaveDataPresent_00", &ScreenHardMode::m218, &ScreenHardMode::m219,
    &ScreenHardMode::m220, &ScreenHardMode::m221, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee810(
    ++ksys::sUnk_71025cb4c8, "::StateID_NoAoC_HardModeSaveDataPresent_01", &ScreenHardMode::m222, &ScreenHardMode::m223,
    &ScreenHardMode::m224, &ScreenHardMode::m225, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee870(
    ++ksys::sUnk_71025cb4c8, "::StateID_NoAoC_HardModeSaveDataPresent_02", &ScreenHardMode::m226, &ScreenHardMode::m227,
    &ScreenHardMode::m228, &ScreenHardMode::m229, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee8d0(
    ++ksys::sUnk_71025cb4c8, "::StateID_NoAoC_HardModeSaveDataPresent_03", &ScreenHardMode::m230, &ScreenHardMode::m231,
    &ScreenHardMode::m232, &ScreenHardMode::m233, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee930(
    ++ksys::sUnk_71025cb4c8, "::StateID_EShopJump_00", &ScreenHardMode::m234, &ScreenHardMode::m235,
    &ScreenHardMode::m236, &ScreenHardMode::m237, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee990(
    ++ksys::sUnk_71025cb4c8, "::StateID_EShopJump_01", &ScreenHardMode::m238, &ScreenHardMode::m239,
    &ScreenHardMode::m240, &ScreenHardMode::m241, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenHardMode> sUnk_71025ee9f0(
    ++ksys::sUnk_71025cb4c8, "::StateID_DoNothing", &ScreenHardMode::m242, &ScreenHardMode::m243,
    &ScreenHardMode::m244, &ScreenHardMode::m245, &ksys::sUnk_710250bcd8);

// 0x7100a0bb34 (CSV ScreenHardMode::x): restores the last-play hard mode flag, clears the player track report,
// saves and shows the load/save icon, then waits in the "do nothing" state.
// NON_MATCHING: the two SEAD_ENUM temporaries of checkFlag / setFlag land in [sp,#8] then [sp,#0xc]; ours uses
// the same two slots in the opposite order. Everything else matches.
void ScreenHardMode::x() {
    if (_3704 == 3) {
        const bool on = !aoc::HardModeManager::instance() ||
                        !aoc::HardModeManager::instance()->checkFlag(
                            aoc::HardModeManager::Flag::EnableHardMode);
        if (ksys::PlayReportMgr::instance() &&
            ksys::PlayReportMgr::instance()->getPlayerTrackReporter())
            ksys::PlayReportMgr::instance()->getPlayerTrackReporter()->mBlocks.clear();
        if (aoc::HardModeManager::instance()) {
            aoc::HardModeManager::instance()->setFlag(aoc::HardModeManager::Flag::EnableHardMode, on);
            aoc::HardModeManager::instance()->storeIsLastPlayHardModeFlag();
        }
        SaveSystem::instance()->sub_71009145F8();
        showLoadSaveIcon(true);
    }
    getStateMachine().changeState(&sUnk_71025ee9f0);
}

// 0x7100a0bd68: the per-frame update: runs the state machine, releases the cursor button on a B press, applies the
// type / content animators' end frames and sets the two buttons from the display mode _3700.
// NON_MATCHING: only block layout. The switch over _3700 is tested 0-before-3 here (the original tests 3 first)
// and the six-case button switch lowers to a bit-test mask (0x39) instead of the original's jump table; same
// instructions and targets.
void ScreenHardMode::m94() {
    getStateMachine().run();
    if (isOpened() && (mButtonGroup->_38 & 2) && isTrigMaybe(2)) {
        switch (_3700) {
        case 1:
        case 2:
            sub_71010AA894();
            mControlPtrs._3638->DownOff(false);
            break;
        case 3:
        case 0:
            sub_71010AA894();
            break;
        }
    }
    if (mControlPtrs._3620->mFlags & 2) {
        mControlPtrs._3620->StopAtMax();
        if (_3700 != -1) {
            mControlPtrs._3610->Stop(f32(_3700));
            mControlPtrs._3618->PlayAuto(1.0f);
        }
        mControlPtrs._3638->setFlag10(false);
        mControlPtrs._3640->setFlag10(false);
    }
    if (mControlPtrs._3618->mFlags & 2) {
        switch (_3700) {
        case 0:
        case 3:
        case 4:
        case 5:
            mControlPtrs._3638->setFlag10(false);
            mControlPtrs._3640->setFlag10(false);
            break;
        case 1:
        case 2:
            mControlPtrs._3638->setFlag10(true);
            mControlPtrs._3640->setFlag10(true);
            break;
        }
    }
}

// 0x7100a0bc24
void ScreenHardMode::m93(sead::Heap*) {
    mControlPtrs._3610 = mLayout->createAnimatorAuto("Type", true);
    mControlPtrs._3620 = mLayout->createAnimatorAuto("ContentOut", true);
    mControlPtrs._3618 = mLayout->createAnimatorAuto("ContentIn", true);
    mControlPtrs._3638 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnL_00"));
    mControlPtrs._3640 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_BtnR_00"));
    mControlPtrs._3648 = mLayout;
    mControlPtrs._3658 = sub_7100BEAFB0("Pa_BtnL_00");
    mControlPtrs._3660 = sub_7100BEAFB0("Pa_BtnR_00");
    _3718 = -1;
    _3700 = -1;
    _3704 = 0;
    _3668.clear();
    getStateMachine().startState(&sUnk_710261ee98);
}

// 0x7100a0bb1c (CSV ScreenHardMode::m6)
void ScreenHardMode::close(s32) {
    if (_3721)
        Screen::close(-1);
}

// 0x7100a0bd2c
void ScreenHardMode::m98() {
    setReservedBoxCursorNodeByButton(mControlPtrs._3638);
    mActiveCursorNode = nullptr;
}

// 0x7100a0bd54
void ScreenHardMode::m99() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a0befc
void ScreenHardMode::m106(eui::AnimButton* button) {
    mButtonGroup->_38 &= ~2;
    const s32 tag = button->mTag;
    switch (tag) {
    case 0x8f:
        invokeSoundLink2Event_("mc_Cancel");
        _3718 = 0x8f;
        _3721 = 0;
        [[fallthrough]];
    case 0x8e:
    case 0x90:
        if (_3720)
            invokeSoundLink2Event_("mc_GameStart");
        else
            invokeSoundLink2Event_("mc_Decide");
        _3718 = tag;
        _3721 = 0;
        break;
    }
}

// 0x7100a0bfa8
void ScreenHardMode::m107(eui::AnimButton* button) {
    if (u32(button->mTag - 0x8e) <= 2)
        _3721 = 1;
}

// 0x7100a0ce70
void ScreenHardMode::m203() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cf90
void ScreenHardMode::m210() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(4);
    _371c = 0;
}

// 0x7100a0cfd0
void ScreenHardMode::m214() {
    _3710 = getStateMachine().getState();
    _3704 = _3708;
    x();
}

// 0x7100a0d004
void ScreenHardMode::m215() {
    if (mState != 0 && mState != 3) {
        if (_371c++ >= 59) {
            _3704 = _3708;
            x();
        }
    }
}

// 0x7100a0d0b0
void ScreenHardMode::m219() {
    switch (_3718) {
    case 0x90:
        _3704 = 5;
        getStateMachine().changeState(&sUnk_71025ee930);
        break;
    case 0x8f:
        getStateMachine().changeState(&sUnk_71025ee810);
        break;
    }
}

// 0x7100a0c660
void ScreenHardMode::m155() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        getStateMachine().changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c784
void ScreenHardMode::m163() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        getStateMachine().changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cb28
void ScreenHardMode::m183() {
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        getStateMachine().changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c844
void ScreenHardMode::m167() {
    switch (_3718) {
    case 0x90:
        getStateMachine().changeState(&sUnk_71025ee330);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cd00
void ScreenHardMode::m195() {
    switch (_3718) {
    case 0x90:
        getStateMachine().changeState(&sUnk_71025ee5d0);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c888
void ScreenHardMode::m170() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0c9fc
void ScreenHardMode::m178() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0cd44
void ScreenHardMode::m198() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0ceb0
void ScreenHardMode::m206() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d0f4
void ScreenHardMode::m222() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d1c0
void ScreenHardMode::m226() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d294
void ScreenHardMode::m230() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
}

// 0x7100a0d368
void ScreenHardMode::m234() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(4);
}

// 0x7100a0d3a0
void ScreenHardMode::m238() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(0);
}

// 0x7100a0c6f8 (CSV ScreenHardMode::m159)
void ScreenHardMode::m159() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c9bc
void ScreenHardMode::m175() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cbc0
void ScreenHardMode::m187() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cc4c
void ScreenHardMode::m191() {
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// NON_MATCHING: the widget name temporary is placed above the FixedSafeString
// in the original's frame
// 0x7100a0c084
void ScreenHardMode::sub_7100A0C084(const sead::SafeString& text, const sead::SafeString& left,
                                    const sead::SafeString& right) {
    sead::FixedSafeString<128> message_set(sHardMode);
    if (!_3668.isEmpty()) {
        message_set = _3668;
        _3668.clear();
    }
    eui::MessageString text_msg;
    eui::MessageString left_msg;
    eui::MessageString right_msg;
    getMessage(message_set, text, &text_msg);
    getMessage(message_set, left, &left_msg);
    getMessage(message_set, right, &right_msg);
    setWidgetString(mControlPtrs._3648, "T_Text_00", text_msg);
    setWidgetString(mControlPtrs._3660, "T_Btn_00", left_msg);
    setWidgetString(mControlPtrs._3658, "T_Btn_00", right_msg);
}

// NON_MATCHING: as sub_7100A0C084
// 0x7100a0c368
void ScreenHardMode::sub_7100A0C368(const sead::SafeString& text, const sead::SafeString& button) {
    sead::FixedSafeString<128> message_set(sHardMode);
    if (!_3668.isEmpty()) {
        message_set = _3668;
        _3668.clear();
    }
    eui::MessageString text_msg;
    eui::MessageString button_msg;
    getMessage(message_set, text, &text_msg);
    getMessage(message_set, button, &button_msg);
    setWidgetString(mControlPtrs._3648, "T_Text_00", text_msg);
    setWidgetString(mControlPtrs._3650, "T_Btn_00", button_msg);
}

// 0x7100a0c614
void ScreenHardMode::m154() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sThree, sOne, sTwo);
}

// 0x7100a0c6ac
void ScreenHardMode::m158() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sThree, sOne, sTwo);
}

// 0x7100a0c738
void ScreenHardMode::m162() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sThree, sOne, sTwo);
}

// 0x7100a0c7d0
void ScreenHardMode::m166() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084("0009", sOne, sTwo);
}

// 0x7100a0c8b8
void ScreenHardMode::m171() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0007", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        _3708 = 3;
        getStateMachine().changeState(&sUnk_71025ee750);
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0c970
void ScreenHardMode::m174() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sThree, sOne, sTwo);
}

// 0x7100a0ca2c
void ScreenHardMode::m179() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0007", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0cadc
void ScreenHardMode::m182() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sFive, sOne, sTwo);
}

// 0x7100a0cb74
void ScreenHardMode::m186() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sFive, sOne, sTwo);
}

// 0x7100a0cc00
void ScreenHardMode::m190() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sFive, sOne, sTwo);
}

// 0x7100a0cc8c
void ScreenHardMode::m194() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084("0010", sOne, sTwo);
}

// 0x7100a0cd74
void ScreenHardMode::m199() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0007", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0ce24
void ScreenHardMode::m202() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084(sFive, sOne, sTwo);
}

// 0x7100a0cee0
void ScreenHardMode::m207() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0007", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        _3704 = 3;
        x();
        break;
    case 0x8f:
        _3704 = 7;
        close(-1);
        break;
    }
}

// 0x7100a0d03c
void ScreenHardMode::m218() {
    _3710 = getStateMachine().getState();
    sub_7100A0BFC8(1);
    sub_7100A0C084("0011", sFourteen, sThirteen);
}

// 0x7100a0d124
void ScreenHardMode::m223() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0012", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        getStateMachine().changeState(&sUnk_71025ee870);
        break;
    case 0x8f:
        getStateMachine().changeState(&sUnk_71025ee8d0);
        break;
    }
}

// 0x7100a0d1f0
void ScreenHardMode::m227() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0007", sOne, sTwo);
    switch (_3718) {
    case 0x90:
        _3708 = 4;
        getStateMachine().changeState(&sUnk_71025ee6f0);
        break;
    case 0x8f:
        getStateMachine().changeState(&sUnk_71025ee8d0);
        break;
    }
}

// 0x7100a0d2c4
void ScreenHardMode::m231() {
    // 0x57 bit 1 of the ContentOut animator
    if (mControlPtrs._3620->mFlags & 2)
        sub_7100A0C084("0011", sFourteen, sThirteen);
    switch (_3718) {
    case 0x90:
        _3704 = 5;
        getStateMachine().changeState(&sUnk_71025ee930);
        break;
    case 0x8f:
        getStateMachine().changeState(&sUnk_71025ee810);
        break;
    }
}

// 0x7100a0d3d0
void ScreenHardMode::m239() {
    if (mControlPtrs._3620->mFlags & 2) {
        _3668 = sSystemWindow;
        sub_7100A0C368("0066", "0067");
    }
    if (_3718 == 0x8e)
        _3704 = 6;
}

void ScreenHardMode::m156() {}

void ScreenHardMode::m160() {}

void ScreenHardMode::m164() {}

void ScreenHardMode::m168() {}

void ScreenHardMode::m172() {}

void ScreenHardMode::m176() {}

void ScreenHardMode::m180() {}

void ScreenHardMode::m184() {}

void ScreenHardMode::m188() {}

void ScreenHardMode::m192() {}

void ScreenHardMode::m196() {}

void ScreenHardMode::m200() {}

void ScreenHardMode::m204() {}

void ScreenHardMode::m208() {}

void ScreenHardMode::m211() {}

void ScreenHardMode::m212() {}

void ScreenHardMode::m216() {}

void ScreenHardMode::m220() {}

void ScreenHardMode::m224() {}

void ScreenHardMode::m228() {}

void ScreenHardMode::m232() {}

void ScreenHardMode::m235() {}

void ScreenHardMode::m236() {}

void ScreenHardMode::m240() {}

void ScreenHardMode::m242() {}

void ScreenHardMode::m243() {}

void ScreenHardMode::m244() {}

bool ScreenHardMode::isEnableControl() const {
    return 1;
}

bool ScreenHardMode::m157(void*) {
    return false;
}

bool ScreenHardMode::m161(void*) {
    return false;
}

bool ScreenHardMode::m165(void*) {
    return false;
}

bool ScreenHardMode::m169(void*) {
    return false;
}

bool ScreenHardMode::m173(void*) {
    return false;
}

bool ScreenHardMode::m177(void*) {
    return false;
}

bool ScreenHardMode::m181(void*) {
    return false;
}

bool ScreenHardMode::m185(void*) {
    return false;
}

bool ScreenHardMode::m189(void*) {
    return false;
}

bool ScreenHardMode::m193(void*) {
    return false;
}

bool ScreenHardMode::m197(void*) {
    return false;
}

bool ScreenHardMode::m201(void*) {
    return false;
}

bool ScreenHardMode::m205(void*) {
    return false;
}

bool ScreenHardMode::m209(void*) {
    return false;
}

bool ScreenHardMode::m213(void*) {
    return false;
}

bool ScreenHardMode::m217(void*) {
    return false;
}

bool ScreenHardMode::m221(void*) {
    return false;
}

bool ScreenHardMode::m225(void*) {
    return false;
}

bool ScreenHardMode::m229(void*) {
    return false;
}

bool ScreenHardMode::m233(void*) {
    return false;
}

bool ScreenHardMode::m237(void*) {
    return false;
}

bool ScreenHardMode::m241(void*) {
    return false;
}

bool ScreenHardMode::m245(void*) {
    return false;
}

}  // namespace uking::ui
