#include "Game/UI/uiScreens.h"

// Slot 4 of the leaf classes (overrides eui::Screen's, which returns 0).
namespace uking::ui {

// 0x7100a0b3a4
s32 ScreenGamePadBG::isEnableControl() const {
    return 1;
}

// 0x7100a6bb70
s32 ScreenTitle::isEnableControl() const {
    return 1;
}

// 0x71009dbcf8
s32 ScreenAppCamera::isEnableControl() const {
    return 1;
}

// 0x7100a09644
s32 ScreenEnergyMeterDLC::isEnableControl() const {
    return 0;
}

// 0x7100a25ba4
s32 ScreenMessageGet::isEnableControl() const {
    return 1;
}

// 0x7100a4e5d4
s32 ScreenShopBtnList5::isEnableControl() const {
    return 1;
}

// 0x7100a4d118
s32 ScreenShopBtnList20::isEnableControl() const {
    return 1;
}

// 0x7100a4b674
s32 ScreenShopBtnList15::isEnableControl() const {
    return 1;
}

// 0x7100a51368
s32 ScreenShopHorse::isEnableControl() const {
    return 1;
}

// 0x7100a00048
s32 ScreenAppTool::isEnableControl() const {
    return 1;
}

// 0x71009d6c18
s32 ScreenAppAlbum::isEnableControl() const {
    return 1;
}

// 0x71009fb200
s32 ScreenAppPictureBook::isEnableControl() const {
    return 1;
}

// 0x71009e7de0
s32 ScreenAppMapDungeon::isEnableControl() const {
    return 1;
}

// 0x7100a1ec1c
s32 ScreenMainScreen::isEnableControl() const {
    return 1;
}

// 0x71009f28a0
s32 ScreenAppMap::isEnableControl() const {
    return 1;
}

// 0x71009de2b0
s32 ScreenAppHome::isEnableControl() const {
    return 1;
}

// 0x7100a22318
s32 ScreenMainShortCut::isEnableControl() const {
    return 1;
}

// 0x7100a3ee2c
s32 ScreenPauseMenu::isEnableControl() const {
    return 1;
}

// 0x7100a0ac38
s32 ScreenGameOver::isEnableControl() const {
    return 1;
}

// 0x7100a4652c
s32 ScreenSaveTransferWindow::isEnableControl() const {
    return 1;
}

// 0x7100a2bcf4
s32 ScreenOptionWindow::isEnableControl() const {
    return 1;
}

// 0x71009d1210
s32 ScreenAmiiboWindow::isEnableControl() const {
    return 1;
}

// 0x7100a031dc
s32 ScreenControllerWindow::isEnableControl() const {
    return 1;
}

// 0x7100a68b64
s32 ScreenSystemWindow01::isEnableControl() const {
    return 1;
}

// 0x7100a65df0
s32 ScreenSystemWindow00::isEnableControl() const {
    return 1;
}

// 0x7100a32f04
s32 ScreenPauseMenuRecipe::isEnableControl() const {
    return 1;
}

// 0x7100a3242c
s32 ScreenPauseMenuMantan::isEnableControl() const {
    return 1;
}

// 0x7100a2c3a0
s32 ScreenPauseMenuEiketsu::isEnableControl() const {
    return 1;
}

// 0x71009fcd4c
s32 ScreenAppSystemWindow::isEnableControl() const {
    return 1;
}

// 0x7100a066d0
s32 ScreenDLCWindow::isEnableControl() const {
    return 1;
}

// 0x7100a5af20
s32 ScreenStaffRollDLC::isEnableControl() const {
    return 1;
}

// 0x7100a100cc
s32 ScreenMainHardMode::isEnableControl() const {
    return 0;
}

// 0x7100a53960
s32 ScreenSkip::isEnableControl() const {
    return 1;
}

// 0x7100a043b8
s32 ScreenDemoStart::isEnableControl() const {
    return 1;
}

// 0x71009f2e90
s32 ScreenAppMenuBtn::isEnableControl() const {
    return 1;
}

}  // namespace uking::ui
