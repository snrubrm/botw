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

ScreenMessageDialog* getSomeMessageSpStuff() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::Unk76);
    if (sead::DynamicCast<ScreenMessageDialog>(screen))
        return static_cast<ScreenMessageDialog*>(screen);
    screen = eui::ScreenMgr::instance()->getScreen(ScreenId::Unk17);
    if (sead::DynamicCast<ScreenMessageDialog>(screen))
        return static_cast<ScreenMessageDialog*>(screen);
    return sead::DynamicCast<ScreenMessageDialog>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MessageDialog));
}

// 0x71010a5888
bool UI::sub_71010A5888() {
    auto* dialog = getSomeMessageSpStuff();
    return dialog && !dialog->isClosed();
}

// 0x71010a5a54
bool UI::sub_71010A5A54() {
    auto* screen = sead::DynamicCast<ScreenMessage3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::Message3D));
    return screen && !screen->isClosed();
}

// 0x71010a5b0c
bool UI::sub_71010A5B0C(ksys::act::Actor* actor) {
    auto* screen = sead::DynamicCast<ScreenMessage3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::Message3D));
    return screen && screen->sub_71010AE9E8(actor);
}

// 0x71010a5c68
bool UI::sub_71010A5C68() {
    auto* dialog = getSomeMessageSpStuff();
    return dialog && dialog->_350 == 10;
}

// 0x71010a70e4
s32 UI::sub_71010A70E4() {
    auto* dialog = getSomeMessageSpStuff();
    if (!dialog)
        return _98;
    return dialog->_5ec;
}

// 0x71010a5cfc
bool UI::sub_71010A5CFC() {
    auto* screen = sead::DynamicCast<ScreenMainDungeon>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MainDungeon));
    return screen && screen->_300 == 3;
}

// 0x71010a5db0
bool UI::sub_71010A5DB0() {
    auto* screen = sead::DynamicCast<ScreenMainDungeon>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MainDungeon));
    return screen && screen->_2fc == 3;
}

// 0x71010a5e64
bool UI::sub_71010A5E64() {
    auto* screen = sead::DynamicCast<ScreenMainDungeon>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::MainDungeon));
    return screen && screen->_304 == 3;
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
