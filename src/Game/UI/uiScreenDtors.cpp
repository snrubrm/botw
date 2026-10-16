#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiScreens.h"

// The trivial destructors of the Screen<Name> classes (defaulted: they tail-call ScreenEx's). Defining them here
// emits the vtables / RTTI of these classes in this TU.
namespace uking::ui {

ScreenGamePadBG::~ScreenGamePadBG() = default;
ScreenWolfLinkHeartGauge::~ScreenWolfLinkHeartGauge() = default;
ScreenMainHorse::~ScreenMainHorse() = default;

// 0x7100a10cd4
void ScreenMainHorse::m101() {
    _3808->disableKeepLinked();
    _3840->disableKeepLinked();
    _3848->disableKeepLinked();
    for (s32 i = 0; i < 10; ++i) {
        _3678[i]->disableKeepLinked();
        _3718[i]->disableKeepLinked();
        _36c8[i]->disableKeepLinked();
    }
    _3810->disableKeepLinked();
    _3818->disableKeepLinked();
    _3820->disableKeepLinked();
}

// 0x7100a102cc
void ScreenMainHorse::sub_7100A102CC() {
    if (isClosed())
        return;
    if (ksys::gdt::getFlag_Horse_IsOnChargePenalty()) {
        for (s32 i = 0; i < _3868; ++i)
            _3718[i]->Stop(1.0f);
        _386c = 0;
        _3850.init(1.0f);
    } else if (_3868 != ksys::gdt::getFlag_Horse_CurrentChargeNum()) {
        _3850.init(1.0f);
    } else if (_3850.isDone()) {
        close(-1);
    }
    _3850.update();
}
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
