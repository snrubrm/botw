#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

// Helpers around the two fade screens (ScreenFadeDemo, Fade) of eui::ScreenMgr. The CSV names the first
// group evt::S7::*; none of them uses `this`.
namespace uking::ui {

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

// 0x71008aeac4 (CSV evt::S7::closeFadeScreens)
bool closeFadeScreens() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->close(-4);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->close(-4);
    return closeFadeStatus();
}

// 0x71008ae6b8
bool closeFadeAndFadeStatus() {
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->open(3);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->close(-1);
    return closeFadeStatus();
}

}  // namespace uking::ui
