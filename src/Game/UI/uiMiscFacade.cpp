#include "Game/UI/euiScreen.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include <prim/seadSafeString.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/AI/aiGoronHeroDescendentRoot.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

// UI wrapper functions around unidentified UI singletons (the 0x7100a94000 TU).
namespace uking::ui {

// 0x7100aa8dd4
bool sub_7100AA8DD4() {
    if (!uiManagerInitialised())
        return false;
    return Manager::instance()->isPausedMaybe();
}

// 0x7100a9baec
bool sub_7100A9BAEC(s32 state) {
    auto* manager = Manager::instance();
    bool result = manager->_c4 == state;
    switch (state) {
    case 18:
    case 19:
    case 23:
    case 27:
        manager->_c4 = -1;
        break;
    case 0: {
        if (manager->_c4 != state)
            return false;
        auto* screen_mgr = eui::ScreenMgr::instance();
        if (!screen_mgr)
            return true;
        return screen_mgr->getTargetFlag(2) != 0;
    }
    }
    return result;
}

// 0x7366d4
bool isOneHitObliteratorActorName(const sead::SafeString& name) {
    if (name.isEmpty())
        return false;
    return name == "Weapon_Sword_502";
}

// 0x7100a981b0 (placeholder name)
bool sub_7100A981B0() {
    auto* manager = eui::ScreenMgr::instance();
    if (!manager)
        return false;
    auto* screen = sead::DynamicCast<ScreenMessageTips>(manager->getScreen(ScreenId::MessageTips));
    if (!screen)
        return false;
    return screen->sub_71010A87F0(18);
}

// 0x7100a96614 (placeholder name): loads and opens the GameOver screen.
bool sub_7100A96614() {
    bool opened = false;
    if (eui::ScreenMgr::instance()) {
        createAndLoadScreenIfNeededImpl(ScreenId::GameOver, nullptr);
        if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::GameOver)) {
            opened = true;
            screen->open(1);
        }
    }
    return opened;
}

// 0x7100a963c0
bool sub_7100A963C0(const sead::SafeString& item, s32 option) {
    bool opened = false;
    if (auto* manager = eui::ScreenMgr::instance()) {
        if (auto* screen = sead::DynamicCast<ScreenPickUp>(manager->getScreen(ScreenId::PickUp))) {
            opened = true;
            screen->setItemAndOpen(item, true);
        }
    }
    return opened;
}

// NON_MATCHING: the original keeps the result in a callee-saved register that is cleared right after the prologue
// (`mov w21, wzr` before the actor test); ours returns the null actor register / sinks the constants
bool openPickUpScreen(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* manager = eui::ScreenMgr::instance();
    if (!manager)
        return false;
    if (auto* screen = sead::DynamicCast<ScreenPickUp>(manager->getScreen(ScreenId::PickUp))) {
        screen->setItemAndOpen(actor->getName(), true);
        return true;
    }
    return false;
}

void increasePouchNumImpl(const sead::SafeString& name, s32 count) {
    if (auto* mgr = PauseMenuDataMgr::instance())
        mgr->increasePouchNum(name, count, nullptr, nullptr);
}

void showInfoOverlayWithString(s32 type, const sead::SafeString& text);

// Free helpers called by the wrappers below (placeholder names, declared only).
void sub_71009F8420(s32 a1);
void sub_71009D3FB0(s32 a1, s32 a2, const sead::SafeString* name);
void sub_71009E7CE8(s32 a1);
void sub_71009FD6C0();
bool sub_71009F8450();
bool sub_71009D3E0C();
bool sub_71009E2E94();

// 0x7100a94af0
void sub_7100A94AF0() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 0;
}

// 0x7100a94ac8
bool sub_7100A94AC8() {
    if (auto* s = Unk_71025d6578::instance())
        return s->_3c != 13;
    return false;
}

// 0x7100a94b08
void sub_7100A94B08() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 2;
}

// 0x7100a94b24
void sub_7100A94B24() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 3;
}

// 0x7100a94b40
void sub_7100A94B40(bool a0, bool a1, bool a2) {
    if (auto* s = Unk_71025d6578::instance())
        s->sub_710094B844(a0, a1, a2);
}

// 0x7100a94b70
void sub_7100A94B70(bool a0) {
    if (auto* s = Unk_71025d6578::instance())
        s->sub_710094B8A4(a0);
}

// 0x7100a94b90
void sub_7100A94B90() {
    if (auto* s = Unk_71025d6578::instance())
        s->_49 = 1;
}

// 0x7100a9b584
void sub_7100A9B584(const sead::Vector3f* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->_80 = *a0;
}

// 0x7100a9d03c: the number of obtained rune items (remote bombs count twice).
int sub_7100A9D03C() {
    const s32 magnesis = ksys::gdt::getFlag_IsGet_Obj_Magnetglove();
    const bool stop_timer = ksys::gdt::getFlag_IsGet_Obj_StopTimer();
    s32 count = stop_timer ? (magnesis ? 2 : 1) : magnesis;
    count += ksys::gdt::getFlag_IsGet_Obj_IceMaker();
    count += ksys::gdt::getFlag_IsGet_Obj_Camera();
    if (ksys::gdt::getFlag_IsGet_Obj_RemoteBomb())
        count += 2;
    return count;
}

// 0x7100a9d0b4
void sub_7100A9D0B4(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948CC4(a0);
}

// 0x7100a9d0d4
void sub_7100A9D0D4(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_71009489C0(a0);
}

// 0x7100a9d0f4
bool sub_7100A9D0F4() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 < 0;
    return false;
}

// 0x7100a9d118
bool sub_7100A9D118() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 > 0;
    return false;
}

// 0x7100a9d140
bool sub_7100A9D140() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 == 0;
    return false;
}

// 0x7100a9d168
void sub_7100A9D168(f32 a0, f32 a1, f32 a2) {
    f32 values[10];
    values[0] = a0;
    values[1] = a1;
    values[2] = a2;
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(values);
}

// 0x7100a9d1a0
void sub_7100A9D1A0(const f32* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(a0);
}

// 0x7100a9d1c0
bool sub_7100A9D1C0() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b6c == 0;
    return false;
}

// 0x7100a9d1e8
bool sub_7100A9D1E8() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b6c == 1;
    return false;
}

// 0x7100a9d210
void sub_7100A9D210(f32 a0, f32 a1) {
    f32 values[10];
    values[0] = a0;
    values[1] = a1;
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(values);
}

// 0x7100a9d290
s32 sub_7100A9D290() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b74;
    return 0;
}

// 0x7100a9d2b0
void sub_7100A9D2B0(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948E44(a0);
}

// 0x7100a9d308
bool sub_7100A9D308(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 0;
    return false;
}

// 0x7100a9d344
bool sub_7100A9D344(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 3;
    return false;
}

// 0x7100a9d380
bool sub_7100A9D380(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 2;
    return false;
}

// 0x7100a9d3bc
bool sub_7100A9D3BC(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 1;
    return false;
}

// 0x7100a9d748
void sub_7100A9D748() {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_71009482FC();
}

// 0x7100a9ebec
bool sub_7100A9EBEC() {
    if (auto* s = Unk_71025d69f0::instance())
        return s->sub_710094E920();
    return false;
}

// 0x7100a9f038
void sub_7100A9F038() {
    Unk_71025d69f0::instance()->sub_710094E0A0();
}

// 0x7100a9f000
void sellPictureBookUIEnd() {
    sub_71009F8420(2);
    Unk_71025d69f0::instance()->sub_710094D9F4(3, 1, 0, 0);
}

// 0x7100a9f048
void sub_7100A9F048(int photo_no) {
    sub_71009D3FB0(2, photo_no, &sead::SafeString::cEmptyString);
    Unk_71025d69f0::instance()->sub_710094D9F4(2, 1, 0, 0);
}

// 0x7100a9f0cc
void sub_7100A9F0CC() {
    sub_71009D3FB0(1, -1, &sead::SafeString::cEmptyString);
    Unk_71025d69f0::instance()->sub_710094DCC4(2, 0);
}

// 0x7100a9f08c
void sub_7100A9F08C(const sead::SafeString& name) {
    sub_71009D3FB0(3, -1, &name);
    Unk_71025d69f0::instance()->sub_710094D9F4(2, 1, 0, 0);
}

// 0x7100a9f108
void sub_7100A9F108() {
    sub_71009F8420(1);
    Unk_71025d69f0::instance()->sub_710094DCC4(3, 0);
}

// 0x7100a9f46c
void sub_7100A9F46C(bool a0) {
    sub_71009E7CE8(0);
    Unk_71025d69f0::instance()->sub_710094D9F4(1, 1, 0, a0);
}

// 0x7100a9bfa8 (CSV return0)
bool return0() {
    return false;
}

// 0x7100a9ed74
void sub_7100A9ED74() {
    sub_71009FD6C0();
}

// 0x7100a9f034
bool sellPictureBookUIEnd2() {
    return sub_71009F8450();
}

// 0x7100a9f104
bool sub_7100A9F104() {
    return sub_71009D3E0C();
}

// 0x7100a9f134
bool sub_7100A9F134() {
    return sub_71009F8450();
}

// 0x7100a9f4ac
bool sub_7100A9F4AC() {
    return !sub_71009E2E94();
}

// Empty functions of the TU (CSV nullsub_NNNN).
// 0x7100a9b1b0
void sub_7100A9B1B0() {}
// 0x7100a9b1b4
void sub_7100A9B1B4() {}
// 0x7100a9b1b8
void sub_7100A9B1B8() {}
// 0x7100a9f528
void sub_7100A9F528() {}
// 0x7100a9fd7c
void sub_7100A9FD7C() {}
// 0x7100a9fd80
void sub_7100A9FD80() {}
// 0x7100a9fd84
void sub_7100A9FD84() {}
// 0x7100a9fd88
void sub_7100A9FD88() {}
// 0x7100a9fd8c
void sub_7100A9FD8C() {}
// 0x7100a9fd90
void sub_7100A9FD90() {}

// 0x7100a95918
void showInfoOverlay(s32 type) {
    showInfoOverlayWithString(type, sead::SafeString::cEmptyString);
}

// Declaration only.
bool sub_7100A95808();

void openSkipScreen(bool with_button) {
    auto* manager = eui::ScreenMgr::instance();
    if (!manager)
        return;
    if (auto* screen = sead::DynamicCast<ScreenSkip>(manager->getScreen(ScreenId::Skip))) {
        if (sub_7100A95808())
            screen->m80(true);
        screen->sub_7100A537F8(with_button);
    }
}

// 0x7100a958dc (CSV ui::closeSkipScreen)
void closeSkipScreen() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::Skip))
        screen->close(-1);
}

// 0x7100a98170 (CSV ui::closeScreenLoadingWeapon)
void closeScreenLoadingWeapon() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    if (auto* screen = mgr->getScreen(ScreenId::LoadingWeapon))
        screen->close(-1);
}

// 0x7100a9b248 (CSV ui::isOpenedMessageGet)
bool isOpenedMessageGet() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageGet);
    if (!screen)
        return false;
    return screen->isOpened();
}

// 0x7100a9b278
bool sub_7100A9B278() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageGet);
    if (!screen)
        return true;
    return screen->isClosed();
}

// 0x7100a9e660
bool isPauseMenuScreenNotClosed() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenu);
    if (!screen)
        return false;
    return !screen->isClosed();
}

// 0x7100a9f91c
bool sub_7100A9F91C() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::PlainScreen);
    if (!screen)
        return true;
    return screen->isOpened();
}

// 0x7100a9e358
bool closeFadeStatus() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::FadeStatus);
    if (screen && screen->isOpened()) {
        screen->close(-4);
        return true;
    }
    return false;
}

// 0x7100a9e3c4
void closeFadeStatusScreenImpl() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::FadeStatus);
    if (screen && screen->isOpened())
        screen->close(-4);
}

// 0x7100a9f52c
void loadMapMainFieldLocationMubin() {
    Manager::instance()->sub_7100A7F0D0();
}

// 0x7100a9f53c
bool findDungeonNameForPositionImpl(f32 radius, sead::SafeString* out_name, const sead::Vector3f* pos) {
    return Manager::instance()->sub_7100A7F2EC(radius, out_name, pos);
}

// 0x7100a9f55c
void sub_7100A9F55C(const void* a0, void* a1) {
    Manager::instance()->sub_7100A7F468(a0, a1);
}

// 0x7100a9f5d4
void sub_7100A9F5D4() {
    Manager::instance()->sub_7100A7C71C();
}

// 0x7100a9d2d0
bool sub_7100A9D2D0(s32 idx) {
    auto* manager = Manager::instance();
    auto& slot = manager->_b0[idx - 24];
    bool result = slot == idx;
    slot = -1;
    return result;
}

// 0x7100a9eb64
// NON_MATCHING: the original fetches Manager::instance() before storing the state and keeps it for the call (a local
// `auto* manager` used once; borderline form, not applied)
void sub_7100A9EB64() {
    Unk_71025d69f0::instance()->_2c = 1;
    Manager::instance()->sub_7100A7C9AC();
    Manager::instance()->_64c30 |= 1;
}

// 0x7100a9ebb8
void sub_7100A9EBB8(s32 value) {
    auto* manager = Manager::instance();
    if (!manager)
        return;
    if (value <= 3)
        Unk_71025d69f0::instance()->_2c = value;
    manager->sub_7100A7C9AC();
}

// 0x7100a9a3f8
bool sub_7100A9A3F8() {
    auto* s = UiSubsys1::instance();
    return !(s && s->sub_7100960DF8());
}

// 0x7100a9a49c
void sub_7100A9A49C(const void* a0) {
    if (auto* s = UiSubsys1::instance())
        s->sub_71009645D0(a0);
}

// 0x7100a9a4bc
bool sub_7100A9A4BC() {
    if (auto* s = UiSubsys1::instance())
        return s->sub_71009648A8() != nullptr;
    return false;
}

// 0x7100a9a4e8
bool sub_7100A9A4E8(s32 a0) {
    if (auto* s = UiSubsys1::instance())
        return s->sub_7100964A0C(a0);
    return false;
}

// 0x7100a9a644
void sub_7100A9A644(ksys::act::Actor* actor) {
    if (auto* s = UiSubsys1::instance())
        s->sub_7100963CE8(actor);
}

// 0x7100a9a664
void sub_7100A9A664(const void* a0, s32* out) {
    if (auto* s = UiSubsys1::instance())
        s->sub_71009661DC(a0, out);
    else
        *out = -1;
}

// 0x7100a9a694
void sub_7100A9A694(const UiSubsys1PinArg* a0) {
    UiSubsys1::instance()->sub_7100963C8C(a0);
}

// 0x7100a9f57c
bool sub_7100A9F57C(s32* out_index, const sead::Vector3f& pos, f32 radius) {
    if (auto* s = UiSubsys1::instance())
        return s->sub_710096310C(out_index, &pos, radius);
    return false;
}

// 0x7100a9488c
void sub_7100A9488C() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::HomeMenuCapture))
        screen->close(-1);
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::HomeMenuCapture2))
        screen->close(-1);
}

// 0x7100a980f8
void sub_7100A980F8() {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return;
    auto* screen = mgr->getScreen(ScreenId::LoadingWeapon);
    if (!screen)
        return;
    if (screen->isClosed() || screen->isClosedOrClosing())
        screen->open(2);
}

// 0x7100a9a430
void sub_7100A9A430(const void* a0) {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap);
    if (!screen)
        return;
    if (screen->isClosed())
        return;
    if (auto* s = UiSubsys1::instance())
        s->sub_710096372C(a0);
}

// 0x7100a9a508
// NON_MATCHING: same instruction sequence, but the original keeps the result in w19 (`mov w19, 1` at the shared
// true exit) while ours materialises a separate w8 constant and ands the result (the five-way ||)
bool sub_7100A9A508() {
    return (UiSubsys1::instance() && UiSubsys1::instance()->sub_7100964A0C(0)) ||
           (UiSubsys1::instance() && UiSubsys1::instance()->sub_7100964A0C(1)) ||
           (UiSubsys1::instance() && UiSubsys1::instance()->sub_7100964A0C(2)) ||
           (UiSubsys1::instance() && UiSubsys1::instance()->sub_7100964A0C(3)) ||
           (UiSubsys1::instance() && UiSubsys1::instance()->sub_7100964A0C(4));
}

}  // namespace uking::ui

namespace uking::ai {

// 0x7100a9a6ac (declared in aiGoronHeroDescendentRoot.h; a UI function)
void sub_7100A9A6AC(bool on) {
    ui::UiSubsys1::instance()->sub_7100963C78(on);
}

}  // namespace uking::ai
