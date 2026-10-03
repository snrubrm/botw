#include "Game/UI/uiScreens.h"

// Slot 4 of the leaf classes (overrides eui::Screen's, which returns 0).
namespace uking::ui {

// 0x7100a0b3a4
s32 ScreenGamePadBG::m4() {
    return 1;
}

// 0x7100a6bb70
s32 ScreenTitle::m4() {
    return 1;
}

// 0x71009dbcf8
s32 ScreenAppCamera::m4() {
    return 1;
}

// 0x7100a09644
s32 ScreenEnergyMeterDLC::m4() {
    return 0;
}

// 0x7100a25ba4
s32 ScreenMessageGet::m4() {
    return 1;
}

// 0x7100a4e5d4
s32 ScreenShopBtnList5::m4() {
    return 1;
}

// 0x7100a4d118
s32 ScreenShopBtnList20::m4() {
    return 1;
}

// 0x7100a4b674
s32 ScreenShopBtnList15::m4() {
    return 1;
}

// 0x7100a51368
s32 ScreenShopHorse::m4() {
    return 1;
}

// 0x7100a00048
s32 ScreenAppTool::m4() {
    return 1;
}

// 0x71009d6c18
s32 ScreenAppAlbum::m4() {
    return 1;
}

// 0x71009fb200
s32 ScreenAppPictureBook::m4() {
    return 1;
}

// 0x71009e7de0
s32 ScreenAppMapDungeon::m4() {
    return 1;
}

// 0x7100a1ec1c
s32 ScreenMainScreen::m4() {
    return 1;
}

// 0x71009f28a0
s32 ScreenAppMap::m4() {
    return 1;
}

// 0x71009de2b0
s32 ScreenAppHome::m4() {
    return 1;
}

// 0x7100a22318
s32 ScreenMainShortCut::m4() {
    return 1;
}

// 0x7100a3ee2c
s32 ScreenPauseMenu::m4() {
    return 1;
}

// 0x7100a0ac38
s32 ScreenGameOver::m4() {
    return 1;
}

// 0x7100a4652c
s32 ScreenSaveTransferWindow::m4() {
    return 1;
}

// 0x7100a2bcf4
s32 ScreenOptionWindow::m4() {
    return 1;
}

// 0x71009d1210
s32 ScreenAmiiboWindow::m4() {
    return 1;
}

// 0x7100a031dc
s32 ScreenControllerWindow::m4() {
    return 1;
}

// 0x7100a68b64
s32 ScreenSystemWindow01::m4() {
    return 1;
}

// 0x7100a65df0
s32 ScreenSystemWindow00::m4() {
    return 1;
}

// 0x7100a32f04
s32 ScreenPauseMenuRecipe::m4() {
    return 1;
}

// 0x7100a3242c
s32 ScreenPauseMenuMantan::m4() {
    return 1;
}

// 0x7100a2c3a0
s32 ScreenPauseMenuEiketsu::m4() {
    return 1;
}

// 0x71009fcd4c
s32 ScreenAppSystemWindow::m4() {
    return 1;
}

// 0x7100a066d0
s32 ScreenDLCWindow::m4() {
    return 1;
}

// 0x7100a5af20
s32 ScreenStaffRollDLC::m4() {
    return 1;
}

// 0x7100a100cc
s32 ScreenMainHardMode::m4() {
    return 0;
}

// 0x7100a53960
s32 ScreenSkip::m4() {
    return 1;
}

// 0x7100a043b8
s32 ScreenDemoStart::m4() {
    return 1;
}

// 0x71009f2e90
s32 ScreenAppMenuBtn::m4() {
    return 1;
}

}  // namespace uking::ui
