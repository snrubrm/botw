#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

Unk_7101EC39D4 sUnk_7101EC39D4;

// 0x710109ed94
// NON_MATCHING: store scheduling only (all stores/calls match: base ctor, the five member
// stores, both vtable pairs, the merged 8-byte _314 zero and the non-tail memset). Ours emits
// mErrorCode second-to-last (after the +0x108 pair) instead of second, keeps the chained _314
// zero after the memset instead of before it, and does not swap the _308/_310 order. Six source
// shapes tried (all-NSDMI, value-init array, full-body, split NSDMI/body, mem-init); the
// scheduler packs differently in each and none reproduces the exact interleaving.
ScreenErrorViewer::ScreenErrorViewer() : Screen() {
    _314 = _318 = 0;
}

ScreenEnergyMeterDLC::ScreenEnergyMeterDLC() : ScreenEx() {}

ScreenPauseMenuMantan::ScreenPauseMenuMantan() : ScreenEx() { sResult = 5; }

// 0x71010a0138
ScreenFadeDemo::ScreenFadeDemo() : Screen() {}

// 0x710109de68
ScreenChangeControllerNN::ScreenChangeControllerNN() : Screen() {}

// 0x71010a2114
ScreenHomeNixSign::ScreenHomeNixSign() : Screen() {}

// 0x710109da7c
ScreenBoxCursorTV::ScreenBoxCursorTV() : Screen() {}

// 0x71010a3ea8
ScreenLoadSaveIcon::ScreenLoadSaveIcon() : Screen() {}

// 0x710109e644
ScreenDemoMessage::ScreenDemoMessage() : Screen() {}

// 0x7100a53dc0
ScreenSousaGuide::ScreenSousaGuide() : ScreenEx() {}

// 0x71010a8454
ScreenMessageTips::ScreenMessageTips() : Screen() {}

// 0x7100a4ad38
ScreenShopBtnList15::ScreenShopBtnList15() : ScreenEx() {}

// 0x7100a09850
ScreenFadeStatus::ScreenFadeStatus() : ScreenEx() {}


ScreenReadyGo::ScreenReadyGo() : ScreenEx() {}

// 0x7100a40da0
ScreenRupee::ScreenRupee() : ScreenEx() {}

// NON_MATCHING: the tail GOT-load/store scheduling differs (the original interleaves the loads with the
// stores and materialises -1 first; ours hoists all three loads and materialises -1 late). All stores match.
// 0x71009fcd64
ScreenAppTool::ScreenAppTool() : ScreenEx() {
    _3740 = -1;
    _3744 = 0;
    sUnk_71025ec540._0 = -1;
    sUnk_71025ec540._4 = 0;
    sUnk_71025ec548 = false;
    sUnk_71025ec549 = false;
    sUnk_71025ec54a = 0;
}

// 0x7100a265ec
ScreenMessageTipsRunTime::ScreenMessageTipsRunTime() : ScreenEx() {}

// 0x7100a0eb2c
ScreenKologNum::ScreenKologNum() : ScreenEx() {}

// 0x71009ceab0
ScreenAkashNum::ScreenAkashNum() : ScreenEx() {}

// 0x7100a22584
ScreenMamoNum::ScreenMamoNum() : ScreenEx() {}

// 0x7100a043c0
ScreenDLCSinJuAkashiNum::ScreenDLCSinJuAkashiNum() : ScreenEx() {}

ScreenGameTitle::ScreenGameTitle() : ScreenEx() {}

ScreenDemoName::ScreenDemoName() : ScreenEx() {}

ScreenDemoNameEnemy::ScreenDemoNameEnemy() : ScreenEx() {}

ScreenShopBG::ScreenShopBG() : ScreenEx() {}

ScreenPauseMenuEiketsu::ScreenPauseMenuEiketsu() : ScreenEx() {}

ScreenHardModeTextDLC::ScreenHardModeTextDLC() : ScreenEx() {}

ScreenEnd::ScreenEnd() : ScreenEx() {}

ScreenLastComplete::ScreenLastComplete() : ScreenEx() {}

ScreenLoadingWeapon::ScreenLoadingWeapon() : ScreenEx() {}

ScreenBootUp::ScreenBootUp() : ScreenEx() {
    sub_7100AA9728();
}

ScreenWolfLinkHeartGauge::ScreenWolfLinkHeartGauge() : ScreenEx() {}

ScreenChangeController::ScreenChangeController() : ScreenEx() {}

ScreenDemoStart::ScreenDemoStart() : ScreenEx() {}

ScreenKeyNum::ScreenKeyNum() : ScreenEx() {}

ScreenShopBtnList5::ScreenShopBtnList5() : ScreenEx() {}

ScreenPauseMenuBG::ScreenPauseMenuBG() : ScreenEx() {}

ScreenSeekPadMenuBG::ScreenSeekPadMenuBG() : ScreenEx() {}

ScreenMainScreenMS::ScreenMainScreenMS() : ScreenEx() {}

ScreenMainScreenHeartIchigekiDLC::ScreenMainScreenHeartIchigekiDLC() : ScreenEx() {}

ScreenAppSystemWindowNoBtn::ScreenAppSystemWindowNoBtn() : ScreenEx() {}

ScreenSystemWindowNoBtn::ScreenSystemWindowNoBtn() : ScreenEx() {}

ScreenOPtext::ScreenOPtext() : ScreenEx() {}

ScreenAppMenuBtn::ScreenAppMenuBtn() : ScreenEx() {}

ScreenHomeMenuCapture::ScreenHomeMenuCapture() : ScreenEx() {}


// 0x7100a0e178
ScreenKeyBoradTextArea::ScreenKeyBoradTextArea() : ScreenEx() {}

// 0x7100a535a8
ScreenSkip::ScreenSkip() : ScreenEx() {}


// 0x7100a0fe64
ScreenMainHardMode::ScreenMainHardMode() : ScreenEx() {}

// 0x71009fbc8c
ScreenAppSystemWindow::ScreenAppSystemWindow() : ScreenEx() {}

// 0x7100a25c4c
ScreenMessageTipsPauseMenu::ScreenMessageTipsPauseMenu() : ScreenEx() {}

// 0x7100a0b044
ScreenGamePadBG::ScreenGamePadBG() : ScreenEx() {}

// 0x7100a0a420
ScreenGameOver::ScreenGameOver() : ScreenEx() {}


// 0x7100a073a4
ScreenDoCommand::ScreenDoCommand() : ScreenEx() {}


// 0x71009d0608
ScreenAmiiboWindow::ScreenAmiiboWindow() : ScreenEx() {}


// 0x7100a32434
ScreenPauseMenuRecipe::ScreenPauseMenuRecipe() : ScreenEx() {}


// 0x7100a60808
ScreenSystemWindow00::ScreenSystemWindow00() : ScreenEx() {}


// 0x7100a68c84
ScreenTime::ScreenTime() : ScreenEx() {}


// 0x7100a0058c
ScreenChallengeWin::ScreenChallengeWin() : ScreenEx() {}


// 0x7100a693e4
ScreenTitle::ScreenTitle() : ScreenEx() {
    _3630 = 0;
    _3628 = 0;
    _3620 = 0;
    _3618 = 0;
    _3610 = 0;
}

// 0x7100a3ef2c
// NON_MATCHING: store/scheduling order only (original zeroes mPtrs first and keeps the s0-s4 link
// order with x2 set before the last two links; ours sinks the mPtrs zero and delays x2).
ScreenPickUp::ScreenPickUp() : ScreenEx() {
    _3660 = &_3670[0];
    _3668 = &_3670[0];
    _3670[0].mNext = &_3670[1];
    _3670[1].mNext = &_3670[2];
    _3670[2].mNext = &_3670[3];
    _3670[3].mNext = &_3670[4];
    _3670[4].mNext = &_3670[5];
    _3670[5].mNext = &_3670[6];
    _3670[6].mNext = nullptr;
    _3650.setBuffer(7, _3cc8);
}

// 0x71010ad85c
// NON_MATCHING: call/store scheduling only (the original sinks the MessageString constructor call below
// the chain and tail-calls the CriticalSection constructor last; ours keeps both member constructor
// calls first). All stores and calls are present and natural.
ScreenMessage3D::ScreenMessage3D() : Screen() {
    _320[0].mNext = &_320[1];
    _310 = &_320[0];
    _318 = &_320[0];
    _320[1].mNext = &_320[2];
    _320[2].mNext = &_320[3];
    _320[3].mNext = nullptr;
    _300.setBuffer(4, _660);
    _690 = 0;
}

// 0x71009dc30c
// NON_MATCHING: init scheduling only (original hoists the memset args before the vtable stores and
// keeps &_36a0 in x20 across the memset call; ours uses a smaller frame without x20). All stores,
// calls and member offsets match.
ScreenAppHome::ScreenAppHome() : ScreenEx() {
    _3660[5] = 0;
    _3660[4] = 0;
    _3660[3] = 0;
    _3660[2] = 0;
    _3660[1] = 0;
    _3660[0] = 0;
}

// rodata words read by the ScreenShopHorse ctor (0x7101eb6d7c = 255, 0x7101eb6d80 = -1;
// owner unknown, names are placeholders)
const u32 sUnk_7101EB6D7C = 255;
const u32 sUnk_7101EB6D80 = 0xFFFFFFFF;

// 0x7100a4ea68
// NON_MATCHING: member-init scheduling only (original stores _3610 and the vtable/constant stores
// before the memsets; ours merges and reorders them). All offsets/values/calls match.
ScreenShopHorse::ScreenShopHorse() : ScreenEx() {
    _3738 = sUnk_7101EB6D7C;
    _373c = _3740 = _3744 = sUnk_7101EB6D80;
}

// 0x7100a58150
ScreenStaffRollDLC::ScreenStaffRollDLC() : ScreenEx() {
    _37f8.setBuffer(2, _3808);
    _38f4 = -1;
    _38f0 = 0;
    _38e8 = 0;
    _38e0 = 0;
    _38d8 = 0;
    _38f8 = -1.0f;
    _38fc = 0;
    _3904 = 3.0f;
    _37f8.clear();
    _3900 = 0;
    _3908 = 3;
    _36b8 = 0;
    _36b0 = 0;
    _36a8 = 0;
    _36a0 = 0;
}

// 0x7100a51698
// NON_MATCHING: init order only (all offsets/values/calls match: the delegate bind, the
// FixedSafeString<64> build and the u64 store are identical). Two differences remain: our lib sead
// zeroes the _3658 PtrArray members via NSDMI (two extra str xzr; the original's older sead did not,
// its memset covered them), and the original hoists the 0x68-byte memset above the member
// constructions (bl) while ours runs it last (tail b).
ScreenShopInfo::ScreenShopInfo() : ScreenEx(), _3768(this, &ScreenShopInfo::sub_7100A51790) {
    memset(_pad_3610, 0, 0x68);
}



}  // namespace uking::ui
