#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

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



}  // namespace uking::ui
