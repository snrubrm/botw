#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Sound/sndSound.h"
#include "Game/UI/uiManager.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_71025d69f0)

// D1 0x710094d8c4, D0 0x710094d8c8
Unk_71025d69f0::~Unk_71025d69f0() = default;

void Unk_71025d69f0::sub_710094D8CC() {
    _28 = 1;
    _38 = 0;
}

void Unk_71025d69f0::sub_710094D8DC() {
    _28 = 1;
    _38 = 0;
}

// 0x710094d8ec
bool Unk_71025d69f0::sub_710094D8EC() {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    if (screen && (screen->isOpened() || screen->isOpening()))
        return false;
    if (sub_7100AA8F30())
        return false;
    _28 = 1;
    sub_71009F8420(0);
    sub_71009D3FB0(0, -1, &sead::SafeString::cEmptyString);
    _44 = 0;
    return true;
}

// 0x710094e920
bool Unk_71025d69f0::sub_710094E920() {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    return screen && !screen->isClosed();
}

void Unk_71025d69f0::sub_710094E480() {
    sub_710094E1C0(false);
}

// NON_MATCHING: the original does not pass `this` to sub_710094E570 (that function, in this TU, never uses it, so
// LLVM drops the argument at the call); should match once sub_710094E570 is decompiled here
// 0x710094e488
bool Unk_71025d69f0::sub_710094E488() {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    if (!screen)
        return false;
    bool flag = false;
    if (!screen->isOpened())
        return false;
    if (!sub_710094E570(_28, &flag))
        return false;
    return !flag;
}

// 0x710094db68 (placeholder name): tells the AppHome screen the download demo state and updates the seek pad menu
// background.
void Unk_71025d69f0::sub_710094DB68(bool is_download_demo) {
    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome)))
        isDownloadDemoStuff(home, is_download_demo);
    if (auto* bg = sead::DynamicCast<ScreenSeekPadMenuBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SeekPadMenuBG))) {
        if (is_download_demo)
            bg->x_2();
        bg->sub_7100A4A8A8();
    }
}

// 0x710094dcc0 (placeholder name): a 4-byte forwarder; the only caller (sub_7100AA8A24) passes the singleton
// as `this`, so it is a member even though the name is unknown.
bool Unk_71025d69f0::sub_710094DCC0() {
    return sub_71009E6B5C();
}

// 0x710094d9f4: switches the app state and closes the map screen unless the new state is the map itself.
// NON_MATCHING: clang schedules the ScreenMgr singleton load after the 0x71009e6b5c call's csel; the original
// loads it in the call's shadow, before the csel (same instructions otherwise).
void Unk_71025d69f0::sub_710094D9F4(s32 a1, s32 a2, s32 a3, s32 a4) {
    const bool b3 = a3 & 1;
    const bool b4 = a4 & 1;
    if (a2 & 1)
        _30 = a1;
    _36 = b4;
    _35 = b3;
    sub_710094DB68(ksys::gdt::getFlag_IsDownloadDemo(false));
    _37 = 1;
    if (a1 != 4) {
        _28 = a1;
    } else if (_2c != 4) {
        _28 = _2c;
        _2c = 4;
    }
    if (_28 != 1) {
        const s32 id = sub_71009E6B5C() ? ScreenId::AppMapDungeon : ScreenId::AppMap;
        if (auto* screen = eui::ScreenMgr::instance()->getScreen(id))
            screen->close(-4);
    }
    sub_710094DCC4(_28, 0);
    _34 = a2 & 1;
    if (Manager::instance()->isPausedMaybe())
        return;
    if (ksys::snd::ExpressionSoundCtrl::instance())
        ksys::snd::ExpressionSoundCtrl::instance()->sub_710104F98C();
}

// 0x710094e0a0: ends the pause state: resets the map screen and re-enables the expression sounds unless the UI
// manager is paused.
void Unk_71025d69f0::sub_710094E0A0() {
    sub_710094E1C0(true);
    _34 = 0;
    if (auto* map = sead::DynamicCast<ScreenAppMap>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap)))
        map->sub_71009EC6CC();
    if (Manager::instance()->isPausedMaybe())
        return;
    if (ksys::snd::ExpressionSoundCtrl::instance())
        ksys::snd::ExpressionSoundCtrl::instance()->sub_710104ED9C();
}

// 0x710094e064
void Unk_71025d69f0::sub_710094E064() {
    const s32 prev = _28;
    _28 = 3;
    sub_71009F8420(3);
    sub_710094DCC4(_28, _28 - prev);
}

// 0x710094f6f8
bool Unk_71025d69f0::sub_710094F6F8() const {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    return screen && screen->sub_71009DD81C();
}

// 0x710094f7ac
bool Unk_71025d69f0::sub_710094F7AC(s32 app) const {
    if (_30 == app)
        return true;
    switch (app) {
    case 0:
        for (s32 i = 0; i < 8; ++i) {
            if (checkIsGetRune(i, 0))
                return true;
        }
        break;
    case 1:
        return true;
    case 2:
        return ksys::gdt::getFlag_IsGet_Obj_Album();
    case 3:
        return ksys::gdt::getFlag_IsGet_Obj_PictureBook();
    }
    return false;
}

}  // namespace uking::ui
