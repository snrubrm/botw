#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiShopMgr.h"

namespace uking::ui {

Unk_7101EC39D4 sUnk_7101EC39D4;

// 0x71025f5450 (see uiScreens.h). The original initialises it from the ScreenStaffRoll TU's
// static initialiser; a constant initialiser gives the same bytes without a runtime initialiser.
Unk_71025f5450 sUnk_71025f5450 = {0, 9999, true, true};


ScreenEnergyMeterDLC::ScreenEnergyMeterDLC() : ScreenEx() {}

ScreenPauseMenuMantan::ScreenPauseMenuMantan() : ScreenEx() { sResult = 5; }


// 0x7100a53dc0
ScreenSousaGuide::ScreenSousaGuide() : ScreenEx() {}


// 0x7100a4ad38
ScreenShopBtnList15::ScreenShopBtnList15() : ScreenEx() {}

// 0x7100a09850
ScreenFadeStatus::ScreenFadeStatus() : ScreenEx() {}


ScreenReadyGo::ScreenReadyGo() : ScreenEx() {}

// 0x7100a40da0
ScreenRupee::ScreenRupee() : ScreenEx() {}

// 0x71009fcd64
ScreenAppTool::ScreenAppTool() : ScreenEx() {
    _3740 = -1;
    _3744 = 0;
    sUnk_71025ec540._0 = -1;
    sUnk_71025ec540._4 = false;
    sUnk_71025ec540._5 = false;
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

// 0x7100a4d9a8
Unk_7102497698::~Unk_7102497698() = default;

// 0x7100a4d9d0
void Unk_7102497698::m9() {
    UiShopMgr::instance()->sub_71009842F8();
}

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
// NON_MATCHING: scheduling only (the original sets w1 = 7 before the last two free-list links).
ScreenPickUp::ScreenPickUp() : ScreenEx() {}


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
ScreenStaffRoll::ScreenStaffRoll() : ScreenEx() {
    _37c0.setBuffer(2, _37d0);
    _38bc = -1;
    _38b8 = 0;
    _38b0 = 0;
    _38a8 = 0;
    _38a0 = 0;
    _38c0 = -1.0f;
    _38c4 = 0;
    _37c0.clear();
    _36b8 = 0;
    _36b0 = 0;
    _36a8 = 0;
    _36a0 = 0;
}

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

// 0x7100a01a54
ScreenControllerWindow::ScreenControllerWindow() : ScreenEx(), _3610() {}

// 0x7100a51698
// NON_MATCHING: init order only (all offsets/values/calls match: the delegate bind, the
// FixedSafeString<64> build and the u64 store are identical). Two differences remain: our lib sead
// zeroes the _3658 PtrArray members via NSDMI (two extra str xzr; the original's older sead did not,
// its memset covered them), and the original hoists the 0x68-byte memset above the member
// constructions (bl) while ours runs it last (tail b).
ScreenDLCWindow::ScreenDLCWindow() : ScreenEx(), _3610() {}

// The original shares the ICF-folded sead::Delegate vtable at 0x7102480298 with ScreenDLCWindow; ours emits its own
// (datarefs-known entry).
ScreenShopBtnList20::ScreenShopBtnList20() : ScreenEx(), _3610() {}

// 0x7100a28c20
ScreenOptionWindow::ScreenOptionWindow() : ScreenEx(), _36c8(this, &ScreenOptionWindow::sub_7100A28CD0) {}

// 0x7100a28cd0
void ScreenOptionWindow::sub_7100A28CD0() {
    _36e8 |= 2;
}

ScreenMessageGet::ScreenMessageGet() : ScreenEx(), _3750(this, &ScreenMessageGet::sub_7100A238C8) {}

ScreenShopInfo::ScreenShopInfo() : ScreenEx(), _3768(this, &ScreenShopInfo::sub_7100A51790) {
    memset(_pad_3610, 0, 0x68);
}


// ScreenAppHome creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102480a98[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102480a88(sUnk_7102480a98);
// 0x71009dbe48
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102480ab0::getEntries() const {
    return &sUnk_7102480a88;
}

// ScreenShopInfo creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_71024981e8[] = {
    {"Pa_ItemName_00", sub_7100A513A4, 0},
    {"Pa_SubTextRupee_00", sub_7100A514A0, 0},
    {"Pa_SubTextMamo_00", sub_7100A514A0, 0},
    {"Pa_Material_", sub_7100A5159C, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_71024981d8(sUnk_71024981e8);
// 0x7100a51374
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498248::getEntries() const {
    return &sUnk_71024981d8;
}

// ScreenSkip creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102498840[] = {
    {"Pa_Skip_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102498830(sUnk_7102498840);
// 0x7100a53578
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498858::getEntries() const {
    return &sUnk_7102498830;
}

// ScreenSousaGuide creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102498e00[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102498df0(sUnk_7102498e00);
// 0x7100a53970
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498e18::getEntries() const {
    return &sUnk_7102498df0;
}

}  // namespace uking::ui
