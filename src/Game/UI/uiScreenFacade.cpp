#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/uiScreens.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
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

// 0x7100a992cc
bool sub_7100A992CC(s32 a0) {
    if (!eui::ScreenMgr::instance())
        return false;
    createAndLoadScreenIfNeededImpl(ScreenId::ReadyGo, nullptr);
    auto* screen =
        sead::DynamicCast<ScreenReadyGo>(eui::ScreenMgr::instance()->getScreen(ScreenId::ReadyGo));
    if (!screen)
        return false;
    screen->open(1);
    screen->sub_7100A40B58(a0);
    return true;
}

// 0x7100a94d54
void sub_7100A94D54() {
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen3D));
    if (screen)
        screen->_4090.sub_710094745C();
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

// 0x7100a94e08
bool sub_7100A94E08() {
    auto* screen = sead::DynamicCast<ScreenMainScreen3D>(eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen3D));
    if (!screen)
        return false;
    return screen->_4010 || screen->_4140;
}

// 0x7100a9a21c
void sub_7100A9A21C(const sead::Vector3f* world_pos, int scale_level) {
    auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap));
    if (!screen)
        return;
    screen->sub_71009EF488(world_pos, scale_level);
    Unk_71025d69f0::instance()->sub_710094D9F4(1, 1, 0, 0);
}

// 0x7100a9f358
void sub_7100A9F358() {
    auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap));
    if (!screen)
        return;
    screen->sub_71009EF57C(1.0f, 1);
}

// 0x7100a9e91c
bool sub_7100A9E91C() {
    if (eui::ScreenMgr::instance()) {
        auto* screen = sead::DynamicCast<ScreenPauseMenu>(eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenu));
        if (screen && !screen->sub_7100A349F4())
            return false;
    }
    if (auto* manager = Manager::instance()) {
        manager->sub_7100A7C904();
        return true;
    }
    return false;
}

// 0x7100a9a308
void sub_7100A9A308(s32 index, bool a1) {
    if (u32(index) > 0xe)
        return;
    auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap));
    if (!screen)
        return;
    screen->sub_71009EF51C(index);
    Unk_71025d69f0::instance()->sub_710094D9F4(1, 1, 0, a1);
}

// 0x7100a9f27c
void sub_7100A9F27C(bool a1) {
    auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap));
    if (!screen)
        return;
    screen->sub_71009EF4EC(4, 1);
    Unk_71025d69f0::instance()->sub_710094D9F4(1, 1, 0, a1);
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

// 0x7100a956c0 (placeholder name)
void sub_7100A956C0(s32 a, s32 b, f32 c) {
    if (b < 1 || (c <= 1e-5f && c >= -1e-5f)) {
        auto* mgr = Manager::instance();
        if (mgr->_a4 != a || !(mgr->_ac > 0.0f))
            return;
    }
    auto* mgr = Manager::instance();
    mgr->_a4 = a;
    mgr->_a8 = b;
    mgr->_ac = c;
    mgr->sub_7100A7A704(4);
}

// 0x7100a95a10 (CSV ui::showCannotPickupBuyAnyMoreMessageMaybe)
void showCannotPickupBuyAnyMoreMessageMaybe(const sead::SafeString& name, bool a2) {
    if (name.isEmpty())
        return;

    al::ByamlIter iter;
    if (!ksys::act::InfoData::instance()->getActorIter(&iter, name.cstr(), true))
        return;

    PouchItemType type;
    bool has_item = false;
    if (ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::CanStack)) {
        const int count = PauseMenuDataMgr::instance()->getItemCount(name, true);
        type = PauseMenuDataMgr::getType(name, &iter);
        has_item = count > 0;
    } else {
        type = PauseMenuDataMgr::getType(name, &iter);
    }

    s32 message;
    if (!has_item) {
        switch (type) {
        case PouchItemType::Sword:
            message = 0;
            break;
        case PouchItemType::Bow:
            message = 2;
            break;
        case PouchItemType::Shield:
            message = 1;
            break;
        case PouchItemType::Food:
            message = 4;
            break;
        default:
            if (!sub_7100A82E28(s32(type)))
                return;
            showInfoOverlayWithString(5, sead::SafeString::cEmptyString);
            return;
        }
    } else {
        message = a2 ? 7 : 6;
    }
    showInfoOverlayWithString(message, sead::SafeString::cEmptyString);
}

// 0x7100a95b44
void sub_7100A95B44(const sead::SafeString& name) {
    if (name.isEmpty())
        return;

    al::ByamlIter iter;
    if (!ksys::act::InfoData::instance()->getActorIter(&iter, name.cstr(), true))
        return;

    PouchItemType type;
    bool has_item = false;
    if (ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::CanStack)) {
        const int count = PauseMenuDataMgr::instance()->getItemCount(name, true);
        type = PauseMenuDataMgr::getType(name, &iter);
        has_item = count > 0;
    } else {
        type = PauseMenuDataMgr::getType(name, &iter);
    }

    s32 message;
    if (has_item) {
        message = 6;
    } else {
        switch (type) {
        case PouchItemType::Sword:
            message = 0;
            break;
        case PouchItemType::Bow:
            message = 2;
            break;
        case PouchItemType::Shield:
            message = 1;
            break;
        case PouchItemType::Food:
            message = 4;
            break;
        default:
            if (!sub_7100A82E28(s32(type)))
                return;
            message = 5;
            break;
        }
    }

    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen));
    if (!screen)
        return;
    screen->sub_7100A1AB84(message);
    Manager::instance()->sub_7100A7A6E4(0);
}

// 0x7100a976c4 (placeholder name)
bool sub_7100A976C4(s32 kind, bool a2) {
    if (!eui::ScreenMgr::instance())
        return false;
    if (auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum))) {
        if (a2)
            screen->sub_7100A0483C(1, kind);
        else
            screen->sub_7100A0483C(0, kind);
        return true;
    }
    createAndLoadScreenIfNeededImpl(ScreenId::DLCSinJuAkashiNum, nullptr);
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum));
    if (a2)
        screen->sub_7100A0483C(1, kind);
    else
        screen->sub_7100A0483C(0, kind);
    return true;
}

// 0x7100a97860 (placeholder name)
void sub_7100A97860(s32 kind) {
    if (!eui::ScreenMgr::instance())
        return;
    if (auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum))) {
        screen->sub_7100A04AAC(kind);
        return;
    }
    createAndLoadScreenIfNeededImpl(ScreenId::DLCSinJuAkashiNum, nullptr);
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum));
    screen->sub_7100A04AAC(kind);
}

// 0x7100a979bc (placeholder name)
bool sub_7100A979BC() {
    if (!eui::ScreenMgr::instance())
        return false;
    if (auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum))) {
        return screen->sub_7100A04A0C();
    }
    createAndLoadScreenIfNeededImpl(ScreenId::DLCSinJuAkashiNum, nullptr);
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum));
    return screen->sub_7100A04A0C();
}

// 0x7100a97b14 (placeholder name)
bool sub_7100A97B14() {
    if (!eui::ScreenMgr::instance())
        return false;
    if (auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum))) {
        return screen->sub_7100A04978();
    }
    createAndLoadScreenIfNeededImpl(ScreenId::DLCSinJuAkashiNum, nullptr);
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum));
    return screen->sub_7100A04978();
}

// 0x7100a97c6c (placeholder name)
void sub_7100A97C6C(s32 add_num, s32 type) {
    if (!eui::ScreenMgr::instance())
        return;
    if (auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum))) {
        screen->sub_7100A04A6C(add_num, type);
        return;
    }
    createAndLoadScreenIfNeededImpl(ScreenId::DLCSinJuAkashiNum, nullptr);
    auto* screen = sead::DynamicCast<ScreenDLCSinJuAkashiNum>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DLCSinJuAkashiNum));
    screen->sub_7100A04A6C(add_num, type);
}

// NON_MATCHING: the original calls ScreenChildEx::GetRuntimeTypeInfoStatic out of line (its callers in the original TU are
// many) while ours inlines it into this function's inline copy of the derived getter
// 0x7100a95808 (placeholder name)
bool sub_7100A95808() {
    auto* child = nn::font::DynamicCast<Unk_710247af10>(getScreenWidgetMaybe(ScreenId::PauseMenu, 1));
    if (!child)
        return false;
    // called through a pointer in the original (not devirtualised)
    return child->mStateMachine.getState()->getId() == (&sUnk_71025d9960)->getId();
}

// NON_MATCHING: the original calls ScreenChildEx::GetRuntimeTypeInfoStatic out of line (its callers in the original TU are
// many) while ours inlines it into this function's inline copy of the derived getter
// 0x7100a9ac84 (placeholder name)
void sub_7100A9AC84(void* a1) {
    if (auto* child = nn::font::DynamicCast<Unk_710247af10>(getScreenWidgetMaybe(ScreenId::PauseMenu, 1)))
        child->sub_71009B62CC(a1);
}

// 0x7100a944d8 (placeholder name)
void sub_7100A944D8() {
    if (auto* thread_mgr = UiLowPrioThreadMgr::instance())
        thread_mgr->pause();
    if (auto* mgr = eui::ScreenMgr::instance()) {
        if (auto* screen = sead::DynamicCast<ScreenEx>(mgr->getScreen(ScreenId::AppCamera)))
            screen->sub_7100A48A18();
    }
    if (auto* manager = Manager::instance())
        manager->_64c30 |= 0x40;
}

// 0x7100a945bc (placeholder name)
void sub_7100A945BC() {
    if (auto* thread_mgr = UiLowPrioThreadMgr::instance())
        thread_mgr->clearQueue();
    if (eui::ScreenMgr::instance()) {
        const s32 ids[] = {ScreenId::AppCamera,  ScreenId::AppMap,        ScreenId::AppMapDungeon,
                           ScreenId::AppAlbum,   ScreenId::AppPictureBook, ScreenId::SystemWindow01};
        for (s32 id : ids) {
            if (auto* screen = sead::DynamicCast<ScreenEx>(eui::ScreenMgr::instance()->getScreen(id)))
                screen->sub_7100A48AAC();
        }
    }
}

// NON_MATCHING: register allocation only (the original keeps the ScreenMgr instance pointer in x23 and the id table in x24)
// 0x7100a946ac (placeholder name)
void sub_7100A946AC() {
    const s32 ids[] = {ScreenId::AppMap,         ScreenId::AppMapDungeon,  ScreenId::AppAlbum,
                       ScreenId::AppPictureBook, ScreenId::SystemWindow01, ScreenId::AkashNum};
    for (s32 id : ids) {
        if (auto* screen = sead::DynamicCast<ScreenEx>(eui::ScreenMgr::instance()->getScreen(id)))
            screen->sub_7100A48B40();
    }
    UiLowPrioThreadMgr::instance()->resume();
}

// 0x7100a947ac (placeholder name)
void sub_7100A947AC() {
    for (s32 id = 0; id != 99; ++id) {
        if (auto* screen = sead::DynamicCast<Screen>(eui::ScreenMgr::instance()->getScreen(id)))
            screen->m125();
    }
    Manager::instance()->sub_7100A7FE9C();
}

// NON_MATCHING: the original masks the bool (`and w8, w19, #1`) separately before each of the two stores, ours once on entry
// 0x7100a94914 (placeholder name)
void sub_7100A94914(bool value) {
    const s32 ids[] = {ScreenId::HomeMenuCapture, ScreenId::HomeMenuCapture2};
    for (s32 id : ids) {
        if (auto* screen =
                sead::DynamicCast<ScreenHomeMenuCapture>(eui::ScreenMgr::instance()->getScreen(id)))
            screen->_3618 = value;
    }
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

// The ids of six screens (26, 73, 24, 25, 27, 10) in the read-only data (0x7101e7f100; defined elsewhere).
extern const s32 sUnk_7101E7F100[6];

// NON_MATCHING: the original keeps the loop over the six ids (pointer-increment form); ours unrolls it
// 0x7100a98038 (placeholder name): any of the six screens (ids 26, 73, 24, 25, 27, 10), other than `excluded_id`,
// is opening / opened and has its byte at 0x100 set
bool sub_7100A98038(s32 excluded_id) {
    bool result = false;
    for (s32 id : sUnk_7101E7F100) {
        bool value = false;
        if (id != excluded_id) {
            auto* screen = eui::ScreenMgr::instance()->getScreen(id);
            if (screen && (screen->isOpening() || screen->isOpened()))
                value = screen->_100 != 0;
        }
        result |= value;
    }
    return result;
}

// 0x7100a9b0b4 (placeholder name)
bool sub_7100A9B0B4() {
    auto* screen = sead::DynamicCast<ScreenChallengeWin>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::ChallengeWin));
    if (screen) {
        if (screen->isOpening())
            return true;
        if (screen->isOpened())
            return true;
    }
    return false;
}

// 0x7100a9f960 (placeholder name)
void sub_7100A9F960(bool open) {
    auto* screen = sead::DynamicCast<ScreenMainHardMode>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MainHardMode));
    if (!screen)
        return;
    if (open) {
        if (screen->isOpening() || screen->isOpened())
            return;
        screen->open(1);
    } else if (screen->isOpened() || screen->isOpening()) {
        screen->close(-1);
    }
}

// 0x7100a9bba8 (placeholder name): the flag of draw target 2 is clear
bool sub_7100A9BBA8() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return false;
    return mgr->getTargetFlag(2) == 0;
}

// 0x7100aa9678 (placeholder name)
void sub_7100AA9678() {
    if (auto* screen = sead::DynamicCast<ScreenSystemWindowNoBtn>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindowNoBtn)))
        screen->sub_7100A60650();
}

}  // namespace uking::ui
