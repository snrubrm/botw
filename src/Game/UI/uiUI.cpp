#include "Game/UI/uiUI.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

void UI::x_0(bool flag) {
    auto* screen = sead::DynamicCast<ScreenMessage3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::Message3D));
    if (screen)
        screen->sub_71010AE7C0(flag);
}

// 0x71010a6e48
void UI::closeMessageTipsScreen() {
    auto* screen = sead::DynamicCast<ScreenMessageTips>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MessageTips));
    if (screen)
        screen->close(-1);
}

// 0x71010a5cac
bool UI::sub_71010A5CAC() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageGet);
    return screen && !screen->isClosed();
}

// 0x71010a6f04
void UI::sub_71010A6F04() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageGet))
        screen->close(-1);
}

// 0x71010a719c
f32 UI::sub_71010A719C() const {
    return 0.53f;
}

// 0x71010a71a8
f32 UI::sub_71010A71A8() const {
    return -3.0f;
}

}  // namespace uking::ui
