#include "Game/UI/uiScreens.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiManager.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// 0x7100a95d04
void showRuntimeTip(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMessageTipsRunTime>(mgr->getScreen(ScreenId::MessageTipsRunTime));
    if (!screen)
        return;
    screen->sub_7100A268AC(a0, 0);
}

// 0x7100a95dc4
void sub_7100A95DC4(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMessageTipsRunTime>(mgr->getScreen(ScreenId::MessageTipsRunTime));
    if (!screen)
        return;
    screen->sub_7100A268AC(a0, 1);
}

// 0x7100a95f5c
void sub_7100A95F5C(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenDoCommand>(mgr->getScreen(ScreenId::DoCommand));
    if (!screen)
        return;
    screen->sub_7100A0772C(a0);
}

// 0x7100a96018
void sub_7100A96018(s64 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(mgr->getScreen(ScreenId::MainScreen3D));
    if (!screen)
        return;
    screen->sub_7100A115E4(a0);
}

// 0x7100a960d4
bool sub_7100A960D4(s64 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(mgr->getScreen(ScreenId::MainScreen3D));
    if (!screen)
        return false;
    return screen->sub_7100A11B10(a0);
}

// 0x7100a96194
bool sub_7100A96194(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(mgr->getScreen(ScreenId::MainScreen3D));
    if (!screen)
        return false;
    return screen->sub_7100A11D34(a0);
}

// 0x7100a96254
void sub_7100A96254(s64 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return;
    screen->sub_7100A1A4E4(a0);
}

// 0x7100a96688
bool sub_7100A96688() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenGameOver>(mgr->getScreen(ScreenId::GameOver));
    if (!screen)
        return false;
    return screen->sub_7100A0A8D8();
}

// 0x7100a96740
bool gameOverScreenStuff() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenGameOver>(mgr->getScreen(ScreenId::GameOver));
    if (!screen)
        return false;
    return screen->sub_7100A0A914();
}

// 0x7100a96a40
bool sub_7100A96A40() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    screen->sub_7100A410D8(2);
    return true;
}

// 0x7100a96afc
void sub_7100A96AFC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return;
    screen->sub_7100A41558();
}

// 0x7100a96bb0
bool sub_7100A96BB0() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    return screen->sub_7100A41440();
}

// 0x7100a96c68
bool triggerRupeeCountScreen() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    return screen->sub_7100A41354(0);
}

// 0x7100a96d24
bool sub_7100A96D24() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    screen->sub_7100A414A0();
    return true;
}

// 0x7100a96eb8
void sub_7100A96EB8() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return;
    screen->sub_7100A0F098();
}

// 0x7100a96f6c
bool sub_7100A96F6C() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return false;
    return screen->sub_7100A0F038();
}

// 0x7100a97024
bool sub_7100A97024() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return false;
    return screen->sub_7100A0EFA4();
}

// 0x7100a970dc
void sub_7100A970DC(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return;
    screen->sub_7100A0F110(a0);
}

// 0x7100a9732c
void sub_7100A9732C() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return;
    screen->sub_71009CF058();
}

// 0x7100a973e0
bool sub_7100A973E0() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return false;
    return screen->sub_71009CEFBC();
}

// 0x7100a97498
bool sub_7100A97498() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return false;
    return screen->sub_71009CEF28();
}

// 0x7100a97550
void sub_7100A97550(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return;
    screen->sub_71009CF01C(a0);
}

// 0x7100a97f80
bool sub_7100A97F80() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMamoNum>(mgr->getScreen(ScreenId::MamoNum));
    if (!screen)
        return false;
    screen->sub_7100A22B98();
    return true;
}

// 0x7100a98ae4
bool sub_7100A98AE4() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ShopHorse, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->sub_7100A4EBA0(0);
    return true;
}

// 0x7100a98bb0
bool sub_7100A98BB0() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ShopHorse, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->sub_7100A4EBA0(1);
    return true;
}

// 0x7100a98ee4
bool sub_7100A98EE4() {
    if (!eui::ScreenMgr::instance())
        return false;
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->close(-1);
    return true;
}

// 0x7100a98fa8
bool sub_7100A98FA8() {
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    return screen && !screen->isClosed();
}

// 0x7100a98c80
bool sub_7100A98C80() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ShopHorse, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->sub_7100A4EBA0(2);
    return true;
}

// 0x7100a98d4c
bool sub_7100A98D4C() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ShopHorse, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->sub_7100A4EBA0(3);
    return true;
}

// 0x7100a98e18
bool sub_7100A98E18() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ShopHorse, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopHorse>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopHorse));
    if (!screen)
        return false;
    screen->sub_7100A4EBA0(4);
    return true;
}

// 0x7100a991c0
bool sub_7100A991C0() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainShortCut>(mgr->getScreen(ScreenId::MainShortCut));
    if (!screen)
        return false;
    return screen->sub_7100A20DD0();
}

// 0x7100a993bc
bool sub_7100A993BC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenReadyGo>(mgr->getScreen(ScreenId::ReadyGo));
    if (!screen)
        return false;
    return screen->sub_7100A40BF8();
}

// 0x7100a99560
bool minigameScreenHideTimer() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(0, 0);
}

// 0x7100a996c4
void minigameScreenMove() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return;
    screen->sub_7100A28088();
}

// 0x7100a99860
bool sub_7100A99860() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(1, 0);
}

// 0x7100a99a08
bool sub_7100A99A08() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(2, 0);
}

// 0x7100a99bb0
bool sub_7100A99BB0() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(3, 0);
}

// 0x7100a99d70
bool sub_7100A99D70() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(4, 0);
}

// 0x7100a99e2c
bool sub_7100A99E2C() {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->openMinigameScreen(5, 0);
}

// 0x7100a99fe8
bool sub_7100A99FE8() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenMiniGame>(mgr->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    return screen->sub_7100A275EC(6, 0);
}

// 0x7100a9a0a4
bool sub_7100A9A0A4(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    screen->sub_7100A410D8(0);
    return true;
}

// 0x7100a9a160
bool sub_7100A9A160() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    return screen->sub_7100A41354(1);
}

// 0x7100a9a938
bool sub_7100A9A938(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenAppMap>(mgr->getScreen(ScreenId::AppMap));
    if (!screen)
        return true;
    return screen->sub_71009EF5A8(a0);
}

// 0x7100a9a9f4
bool sub_7100A9A9F4() {
    auto* mgr = eui::ScreenMgr::instance();
    auto* screen = sead::DynamicCast<ScreenAppMap>(mgr->getScreen(ScreenId::AppMap));
    if (!screen)
        return false;
    return screen->sub_71009E9F10();
}

// 0x7100a9affc
bool sub_7100A9AFFC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    return screen->sub_7100A1E1E0();
}

// 0x7100a9e7ac
bool sub_7100A9E7AC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return true;
    auto* screen = sead::DynamicCast<ScreenPauseMenu>(mgr->getScreen(ScreenId::PauseMenu));
    if (!screen)
        return true;
    return screen->sub_7100A34A10();
}

// 0x7100a9e864
bool sub_7100A9E864() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return true;
    auto* screen = sead::DynamicCast<ScreenPauseMenu>(mgr->getScreen(ScreenId::PauseMenu));
    if (!screen)
        return true;
    return screen->sub_7100A349F4();
}

// 0x7100a9ecbc
bool sub_7100A9ECBC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenAppTool>(mgr->getScreen(ScreenId::AppTool));
    if (!screen)
        return false;
    return screen->sub_71009FD674();
}

// 0x7100a9ef44
void sellPictureBookDemo(s32 a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenAppPictureBook>(mgr->getScreen(ScreenId::AppPictureBook));
    if (!screen)
        return;
    screen->sub_71009F8510(a0);
}

// 0x7100a94bac
void sub_7100A94BAC() {
    if (auto* unk = Unk_71025d6578::instance())
        unk->sub_710094BE14();
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenPauseMenuInfo>(mgr->getScreen(ScreenId::PauseMenuInfo));
    if (!screen)
        return;
    screen->sub_7100A31BE0();
}

// 0x7100a95008
bool sub_7100A95008() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(0);
    return screen->sub_7100A1A1C4(0, true);
}

// 0x7100a950dc
bool sub_7100A950DC() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(2);
    return screen->sub_7100A1A1C4(1, true);
}

// 0x7100a9534c
bool sub_7100A9534C() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(1);
    return screen->sub_7100A1A1C4(4, true);
}

// 0x7100a95420
bool sub_7100A95420() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(5);
    screen->sub_7100A1AB58(2);
    return screen->sub_7100A1A1C4(6, true);
}

// 0x7100a95500
bool sub_7100A95500() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(5);
    screen->sub_7100A1AB58(3);
    return screen->sub_7100A1A1C4(6, true);
}

// 0x7100a955e0
bool sub_7100A955E0() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return false;
    Manager::instance()->sub_7100A7A704(5);
    screen->sub_7100A1AB58(4);
    return screen->sub_7100A1A1C4(6, true);
}

// 0x7100a95924
void showInfoOverlayWithString(s32 type, const sead::SafeString& text) {
    if (sub_7100AA8F10())
        return;
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return;
    screen->showInfoOverlayWithString(type, text);
    Manager::instance()->sub_7100A7A6E4(0);
}

// 0x7100a95e84
bool sub_7100A95E84(s32 command) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenDoCommand>(mgr->getScreen(ScreenId::DoCommand));
    if (!screen)
        return false;
    if (!screen->setCommand(command))
        return false;
    Manager::instance()->sub_7100A7A704(3);
    return true;
}

// 0x7100a96310
s32 sub_7100A96310() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return -1;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return -1;
    return screen->_3704;
}

// 0x7100a96568
void mainScreen3DStuff() {
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen3D));
    if (!screen)
        return;
    screen->_3f38 = true;
}

// 0x7100a967f8
bool sub_7100A967F8() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenGameOver>(mgr->getScreen(ScreenId::GameOver));
    if (!screen)
        return false;
    return screen->_3610 != 0;
}

// 0x7100a968b4
s32 sub_7100A968B4() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return 6;
    auto* screen = sead::DynamicCast<ScreenGameOver>(mgr->getScreen(ScreenId::GameOver));
    if (!screen)
        return 6;
    return screen->_3614;
}

// 0x7100a97198
bool sub_7100A97198() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return false;
    return screen->_3634 == 2;
}

// 0x7100a9760c
bool sub_7100A9760C() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return false;
    return screen->_3634 == 2;
}

// 0x7100a97ddc
bool sub_7100A97DDC(s32 value) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(mgr->getScreen(ScreenId::DLCSinJuAkashiNum));
    if (!screen)
        return false;
    if (screen->_3638 != 2)
        return false;
    return screen->_3688 == value;
}

// 0x7100a96964
bool sub_7100A96964(bool a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenRupee>(mgr->getScreen(ScreenId::Rupee));
    if (!screen)
        return false;
    if (a0)
        screen->sub_7100A410D8(3);
    else
        screen->sub_7100A410D8(1);
    return true;
}

// 0x7100a96ddc
bool sub_7100A96DDC(bool a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenKologNum>(mgr->getScreen(ScreenId::KologNum));
    if (!screen)
        return false;
    if (a0)
        screen->sub_7100A0EF5C(1);
    else
        screen->sub_7100A0EF5C(0);
    return true;
}

// 0x7100a97250
bool sub_7100A97250(bool a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenAkashNum>(mgr->getScreen(ScreenId::AkashNum));
    if (!screen)
        return false;
    if (a0)
        screen->sub_71009CEEE0(1);
    else
        screen->sub_71009CEEE0(0);
    return true;
}

// 0x7100a97ea4
bool sub_7100A97EA4(bool a0) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    auto* screen = sead::DynamicCast<ScreenMamoNum>(mgr->getScreen(ScreenId::MamoNum));
    if (!screen)
        return false;
    if (a0)
        screen->sub_7100A22A80(1);
    else
        screen->sub_7100A22A80(0);
    return true;
}

// 0x7100a99474
bool openMinigameScreenForTimer(bool count_down) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(0, 0))
        return false;
    screen->_3668 = count_down;
    return true;
}

// 0x7100a9961c
void minigameScreenUpdateTimer(s64 time_ms) {
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return;
    screen->_3660 = time_ms;
}

// 0x7100a99774
bool setShowGolfCount(const sead::SafeString& counter_name) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(1, 0))
        return false;
    screen->sub_7100A280A4(counter_name);
    return true;
}

// 0x7100a9991c
bool sub_7100A9991C(const sead::SafeString& counter_name) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(2, 0))
        return false;
    screen->sub_7100A2813C(counter_name);
    return true;
}

// 0x7100a99ac4
bool setShowFlyDistance(const sead::SafeString& distance) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(3, 0))
        return false;
    screen->sub_7100A28264(distance);
    return true;
}

// 0x7100a99c6c
bool setShowCheckPoint(s32 icon_type, const sead::SafeString& counter_name) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(4, 0))
        return false;
    screen->sub_7100A28318(counter_name);
    screen->sub_7100A283B0(icon_type);
    return true;
}

// 0x7100a99efc
bool setShowRaceResult(s32 result_type) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::MiniGame, nullptr);
    auto* screen = sead::DynamicCast<ScreenMiniGame>(eui::ScreenMgr::instance()->getScreen(ScreenId::MiniGame));
    if (!screen)
        return false;
    if (!screen->openMinigameScreen(6, 0))
        return false;
    screen->sub_7100A28418(result_type);
    return true;
}

}  // namespace uking::ui
