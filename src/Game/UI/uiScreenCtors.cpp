#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

ScreenReadyGo::ScreenReadyGo() : ScreenEx() {}

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

}  // namespace uking::ui
