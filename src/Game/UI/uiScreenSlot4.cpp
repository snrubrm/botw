#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

// Slot 4 of the leaf classes (overrides eui::Screen's, which returns 0).
namespace uking::ui {

// 0x7100a537f8
void ScreenSkip::sub_7100A537F8(bool with_button) {
    open(1);
    if (_3610) {
        const s32 icon = with_button ? 10 : 8;
        if (_3618 != icon) {
            _3618 = icon;
            sub_7100AA34A4(_3610->_20, "T_Icon_00", icon);
        }
    }
}

// 0x7100a0b3a4
bool ScreenGamePadBG::isEnableControl() const {
    return 1;
}

// 0x7100a6bb70
bool ScreenTitle::isEnableControl() const {
    return 1;
}

// 0x71009dbcf8
bool ScreenAppCamera::isEnableControl() const {
    return 1;
}

// 0x7100a09644
bool ScreenEnergyMeterDLC::isEnableControl() const {
    return 0;
}

// 0x7100a25ba4
bool ScreenMessageGet::isEnableControl() const {
    return 1;
}

// 0x7100a4e5d4
bool ScreenShopBtnList5::isEnableControl() const {
    return 1;
}

// 0x7100a4d118
bool ScreenShopBtnList20::isEnableControl() const {
    return 1;
}

// 0x7100a4b674
bool ScreenShopBtnList15::isEnableControl() const {
    return 1;
}

// 0x7100a4b574
bool ScreenShopBtnList15::sub_7100A4B574() const {
    return mButtonGroup->FindDownButton() != nullptr;
}

// 0x7100a4cef0
bool ScreenShopBtnList20::sub_7100A4CEF0() const {
    return mButtonGroup->FindDownButton() != nullptr;
}

// 0x7100a51368
bool ScreenShopHorse::isEnableControl() const {
    return 1;
}

// 0x7100a00048
bool ScreenAppTool::isEnableControl() const {
    return 1;
}

// 0x71009d6c18
bool ScreenAppAlbum::isEnableControl() const {
    return 1;
}

// 0x71009fb200
bool ScreenAppPictureBook::isEnableControl() const {
    return 1;
}

// 0x71009e7de0
bool ScreenAppMapDungeon::isEnableControl() const {
    return 1;
}

// 0x7100a1ec1c
bool ScreenMainScreen::isEnableControl() const {
    return 1;
}

// 0x71009f28a0
bool ScreenAppMap::isEnableControl() const {
    return 1;
}

// 0x71009de2b0
bool ScreenAppHome::isEnableControl() const {
    return 1;
}

// 0x7100a22318
bool ScreenMainShortCut::isEnableControl() const {
    return 1;
}

// 0x7100a3ee2c
bool ScreenPauseMenu::isEnableControl() const {
    return 1;
}

// 0x7100a0ac38
bool ScreenGameOver::isEnableControl() const {
    return 1;
}

// 0x7100a4652c
bool ScreenSaveTransferWindow::isEnableControl() const {
    return 1;
}

// 0x7100a2bcf4
bool ScreenOptionWindow::isEnableControl() const {
    return 1;
}

// 0x71009d1210
bool ScreenAmiiboWindow::isEnableControl() const {
    return 1;
}

// 0x7100a031dc
bool ScreenControllerWindow::isEnableControl() const {
    return 1;
}

// 0x7100a68b64
bool ScreenSystemWindow01::isEnableControl() const {
    return 1;
}

// 0x7100a65df0
bool ScreenSystemWindow00::isEnableControl() const {
    return 1;
}

// 0x7100a32f04
bool ScreenPauseMenuRecipe::isEnableControl() const {
    return 1;
}

// 0x7100a3242c
bool ScreenPauseMenuMantan::isEnableControl() const {
    return 1;
}

// 0x7100a2c3a0
bool ScreenPauseMenuEiketsu::isEnableControl() const {
    return 1;
}

// 0x71009fcd4c
bool ScreenAppSystemWindow::isEnableControl() const {
    return 1;
}

// 0x7100a066d0
bool ScreenDLCWindow::isEnableControl() const {
    return 1;
}

// 0x7100a5af20
bool ScreenStaffRollDLC::isEnableControl() const {
    return 1;
}

// 0x7100a100cc
bool ScreenMainHardMode::isEnableControl() const {
    return 0;
}

// 0x7100a53960
bool ScreenSkip::isEnableControl() const {
    return 1;
}

// 0x7100a043b8
bool ScreenDemoStart::isEnableControl() const {
    return 1;
}

// 0x71009f2e90
bool ScreenAppMenuBtn::isEnableControl() const {
    return 1;
}

// 0x7100a1e44c (kept out of uiScreenSmall2.cpp, where it would be inlined into the ScreenChallengeWin callers)
f32 ScreenMainScreen::sub_7100A1E44C() {
    return 1.0f;
}

// 0x7100a1ab68
f32 ScreenMainScreen::sub_7100A1AB68() const {
    return _3678.sub_710093695C();
}

// 0x7100a1ab94
void ScreenMainScreen::sub_7100A1AB94() {
    _3678.sub_7100936254(getAnimationStep_(), false);
}

}  // namespace uking::ui
