#include "Game/UI/uiScreens.h"
#include "KingSystem/Event/evtS7.h"
#include "Game/UI/uiUtils.h"

// Helpers around the two fade screens (ScreenFadeDemo, Fade) of eui::ScreenMgr. The CSV names the first
// group evt::S7::*; none of them uses `this`.
namespace uking::ui {

void applyScreenFade(float progress) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = sead::DynamicCast<Fade>(mgr->getScreen(ScreenId::Fade));
    if (screen)
        screen->sub_71010A0EE8(progress);
}

// 0x71008ae818
void sub_71008AE818() {
    sead::DynamicCast<ScreenFadeDemo>(eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo))
        ->sub_71010A01A8(0);
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->open(3);
}

// 0x71008ae8f4
void sub_71008AE8F4() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->close(-4);
}

// 0x71008ae928
bool sub_71008AE928() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->close(-4);
    return closeFadeStatus();
}

// 0x71008ae96c (CSV evt::S7::isFadeDemoScreenOpened)
bool isFadeDemoScreenOpened() {
    return eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->isOpened();
}

// 0x71008ae994 (CSV evt::S7::isFadeScreenOpened)
bool isFadeScreenOpened() {
    return eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->isOpened();
}

// 0x71008aea9c (CSV evt::S7::isFadeScreenClosed)
bool isFadeScreenClosed() {
    return eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->isClosed();
}

// 0x71008ae9bc (CSV evt::S7::isFadeDemoScreenOpenedOrOpening)
bool isFadeDemoScreenOpenedOrOpening() {
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->isOpening())
        return true;
    return eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->isOpened();
}

// 0x71008aea2c (CSV evt::S7::isFadeScreenOpenedOrOpening)
bool isFadeScreenOpenedOrOpening() {
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->isOpening())
        return true;
    return eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->isOpened();
}

// 0x71008ae644
void sub_71008AE644() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->open(3);
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->close(-1);
}

// 0x71008ae6b8
bool closeFadeAndFadeStatus() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->open(3);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->close(-1);
    return closeFadeStatus();
}

}  // namespace uking::ui

namespace ksys::evt {

using namespace uking::ui;

// 0x71008ae2a8
void S7::sub_71008AE2A8(bool a) {
    sead::DynamicCast<ScreenFadeDemo>(eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo))
        ->sub_71010A01A8(a);
    sead::DynamicCast<ScreenFadeDemo>(eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo))
        ->sub_71010A01F8(1);
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->open(1);
}

// 0x71008ae41c
void S7::sub_71008AE41C(bool open_status, bool stop_at_max) {
    sead::DynamicCast<Fade>(eui::ScreenMgr::instance()->getScreen(ScreenId::Fade))
        ->stopColorAnimatorAt(stop_at_max);
    sead::DynamicCast<Fade>(eui::ScreenMgr::instance()->getScreen(ScreenId::Fade))
        ->setStartedMaybe(open_status);
    sead::DynamicCast<Fade>(eui::ScreenMgr::instance()->getScreen(ScreenId::Fade))->x_1(1);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->open(1);
    if (open_status)
        openFadeStatus();
}

// 0x71008ae730
void S7::sub_71008AE730(bool stop_at_max) {
    sead::DynamicCast<Fade>(eui::ScreenMgr::instance()->getScreen(ScreenId::Fade))
        ->stopColorAnimatorAt(stop_at_max);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->open(3);
}

}  // namespace ksys::evt
