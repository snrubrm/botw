#include "Game/UI/uiUI.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(UI)

// D1 0x71010a5814, D0 0x71010a5828
// The body keeps the vtable store of the original (as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }).
UI::~UI() { ; }

void UI::x_0(bool flag) {
    auto* screen = sead::DynamicCast<ScreenMessage3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::Message3D));
    if (screen)
        screen->sub_71010AE7C0(flag);
}

// 0x71010a582c
void UI::init() {
    ksys::gdt::getBoolByName(ksys::gdt::Manager::instance(), &mBalloonTextOn, "BalloonTextOnOff");
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

// 0x71010a5bc8
bool UI::sub_71010A5BC8() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::DemoMessage);
    return screen && !screen->isClosed();
}

// 0x71010a5c18
bool UI::sub_71010A5C18() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageTips);
    return screen && !screen->isClosed();
}

// 0x71010a5c8c
void UI::sub_71010A5C8C() {
    if (auto* dialog = getSomeMessageSpStuff())
        dialog->sub_71010B343C();
}

// 0x71010a7994
void UI::sub_71010A7994(bool flag) {
    if (auto* dialog = getSomeMessageSpStuff())
        dialog->sub_71010B34A0(flag);
}

// 0x71010a6b98
// NON_MATCHING: the original compares `actor` against `_30` as `cmp actor, _30`, ours has the operands swapped
void UI::sub_71010A6B98(ksys::act::Actor* actor) {
    if (!actor || !_30 || _30 == actor) {
        if (auto* dialog = getSomeMessageSpStuff()) {
            dialog->close(-1);
            ksys::snd::SoundMgr::instance()->_48->sub_7101055B44();
        }
    }
}

// 0x71010a6bec
void UI::sub_71010A6BEC(ksys::act::Actor* actor, bool flag) {
    auto* screen = sead::DynamicCast<ScreenMessage3D>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::Message3D));
    if (screen) {
        screen->sub_71010AE548(actor, flag);
        ksys::snd::SoundMgr::instance()->_48->sub_7101055B44();
    }
}

// 0x71010a6d84
void UI::sub_71010A6D84() {
    auto* screen = sead::DynamicCast<ScreenDemoMessage>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DemoMessage));
    if (screen) {
        screen->sub_710109E96C();
        screen->close(-1);
    }
}

// 0x71010a6f40
void UI::sub_71010A6F40() {
    if (_a4 == 2) {
        auto* screen = sead::DynamicCast<ScreenErrorViewer>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::ErrorViewer));
        if (screen)
            screen->close(-1);
    }
}

// 0x71010a7008
bool UI::sub_71010A7008() {
    return u32(_a4 - 3) < 5;
}

// 0x71010a701c
void UI::sub_71010A701C() {
    if (u32(_a4 - 3) <= 4)
        _a4 = 0;
}

// 0x71010a7034
void UI::sub_71010A7034() {
    auto* screen = sead::DynamicCast<ScreenDemoMessage>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::DemoMessage));
    if (screen)
        screen->sub_710109E94C();
}

// 0x71010a7118
void UI::setPlacedItemStockNum(bool choice_mode, s32 stock) {
    const s32 num = (choice_mode && stock < 1) ? 1 : stock;
    mChoiceMode = choice_mode;
    mStockNum = num;
    if (auto* dialog = getSomeMessageSpStuff())
        dialog->sub_71010B34B4(choice_mode, num);
}

// 0x71010a7168
// NON_MATCHING: the two address computations (this + 0x9c / dialog + 0x73c) are emitted in the other order
s32 UI::getTradeItemNum() {
    auto* dialog = getSomeMessageSpStuff();
    return dialog == nullptr ? _9c : dialog->_73c;
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
