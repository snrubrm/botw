#include "Game/UI/uiScreens.h"

// The trivial destructors of the Screen<Name> classes (defaulted: they tail-call ScreenEx's). Defining them here
// emits the vtables / RTTI of these classes in this TU.
namespace uking::ui {

ScreenGamePadBG::~ScreenGamePadBG() = default;
ScreenWolfLinkHeartGauge::~ScreenWolfLinkHeartGauge() = default;
ScreenMainHorse::~ScreenMainHorse() = default;
ScreenReadyGo::~ScreenReadyGo() = default;
ScreenKeyNum::~ScreenKeyNum() = default;
ScreenGameTitle::~ScreenGameTitle() = default;
ScreenDemoName::~ScreenDemoName() = default;
ScreenDemoNameEnemy::~ScreenDemoNameEnemy() = default;
ScreenShopBG::~ScreenShopBG() = default;
ScreenShopBtnList5::~ScreenShopBtnList5() = default;
ScreenShopHorse::~ScreenShopHorse() = default;
ScreenPauseMenuBG::~ScreenPauseMenuBG() = default;
ScreenSeekPadMenuBG::~ScreenSeekPadMenuBG() = default;
ScreenMainScreenMS::~ScreenMainScreenMS() = default;
ScreenMainScreenHeartIchigekiDLC::~ScreenMainScreenHeartIchigekiDLC() = default;
ScreenAppSystemWindowNoBtn::~ScreenAppSystemWindowNoBtn() = default;
ScreenGameOver::~ScreenGameOver() = default;
ScreenMessageTipsPauseMenu::~ScreenMessageTipsPauseMenu() = default;
ScreenAmiiboWindow::~ScreenAmiiboWindow() = default;
ScreenSystemWindowNoBtn::~ScreenSystemWindowNoBtn() = default;
ScreenSystemWindow00::~ScreenSystemWindow00() = default;
ScreenPauseMenuMantan::~ScreenPauseMenuMantan() = default;
ScreenPauseMenuEiketsu::~ScreenPauseMenuEiketsu() = default;
ScreenAppSystemWindow::~ScreenAppSystemWindow() = default;
ScreenHardModeTextDLC::~ScreenHardModeTextDLC() = default;
ScreenEnd::~ScreenEnd() = default;
ScreenLastComplete::~ScreenLastComplete() = default;
ScreenOPtext::~ScreenOPtext() = default;
ScreenLoadingWeapon::~ScreenLoadingWeapon() = default;
ScreenMainHardMode::~ScreenMainHardMode() = default;
ScreenSkip::~ScreenSkip() = default;
ScreenChangeController::~ScreenChangeController() = default;
ScreenDemoStart::~ScreenDemoStart() = default;
ScreenBootUp::~ScreenBootUp() = default;
ScreenAppMenuBtn::~ScreenAppMenuBtn() = default;
ScreenHomeMenuCapture::~ScreenHomeMenuCapture() = default;

}  // namespace uking::ui
