#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::ui {

// 0x71009b9b38
Unk_710247b428::Unk_710247b428(eui::LayoutEx* layout)
    : ScreenChildEx(layout), _130{}, _1a8(nullptr), _1b0{} {}


Unk_710247ae48::~Unk_710247ae48() = default;

// 0x71009b8d58
void Unk_710247af10::m105() {
    if (_300)
        _300->sub_710093F594(true);
    _148->StopAtMin();
    _32c = 0;
}

// 0x71009b8d98
void Unk_710247af10::m106() {}

// 0x71009b9198
s32 Unk_710247af10::m108() { return 0; }

// 0x71009b8db0
void Unk_710247af10::m109() {}

// 0x71009b8db4
void Unk_710247af10::m110() {
    sub_71009B8B6C();
}

// 0x71009b8db8
void Unk_710247af10::m111() {}

// 0x71009b91a0
s32 Unk_710247af10::m112() { return 0; }

// 0x71009b8dbc
void Unk_710247af10::m113() {
    if (auto* manager = ksys::evt::Manager::instance())
        manager->_1d1b0 &= ~2u;
    if (auto* save = SaveSystem::instance())
        save->_1a50 |= 0x1000;
}

// 0x71009b8e00
void Unk_710247af10::m114() {
    if (ksys::evt::Manager::instance()->hasActiveEvent())
        return;
    _148->PlayAuto(-1.0f);
    _128->sub_7100BEB70C();
    mStateMachine.changeState(&sUnk_71025d98a0);
}

// 0x71009b8e64
void Unk_710247af10::m115() {
    if (auto* manager = ksys::evt::Manager::instance())
        manager->_1d1b0 |= 2;
    if (auto* save = SaveSystem::instance())
        save->_1a50 &= ~0x1000;
}

// 0x71009b91a8
s32 Unk_710247af10::m116() { return 0; }

// 0x71009bc05c
s32 Unk_710247b428::m108() { return 0; }

// 0x71009bb594
void Unk_710247b428::m109() {}

// 0x71009bb598
void Unk_710247b428::m110() {
    auto* screen = sead::DynamicCast<ScreenOptionWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::OptionWindow));
    if (!screen || screen->isOpened())
        mStateMachine.changeState(&sUnk_71025d9ec0);
}

// 0x71009bb660
void Unk_710247b428::m111() {}

// 0x71009bc064
s32 Unk_710247b428::m112() { return 0; }

// 0x71009bb664
void Unk_710247b428::m113() {}

// 0x71009bb668
void Unk_710247b428::m114() {
    auto* screen = sead::DynamicCast<ScreenOptionWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::OptionWindow));
    if (screen) {
        if ((screen->_291 & 4) && _1a8) {
            if (ksys::gdt::getFlag_JumpButtonChange())
                _1a8->StopAtMax();
            else
                _1a8->StopAtMin();
        }
        if (!screen->isClosed())
            return;
    }
    mStateMachine.changeState(&sUnk_71025d9e00);
}

// 0x71009bb768
void Unk_710247b428::m115() {}

// 0x71009bc06c
s32 Unk_710247b428::m116() { return 0; }

// 0x71009bb76c
void Unk_710247b428::m117() {}

// 0x71009bb8c8
void Unk_710247b428::m119() {}

// 0x71009bc074
s32 Unk_710247b428::m120() { return 0; }

// 0x71009bb8cc
void Unk_710247b428::m121() {}

// 0x71009bbad0
void Unk_710247b428::m123() {}

// 0x71009bc07c
s32 Unk_710247b428::m124() { return 0; }

// 0x71009bbad4
void Unk_710247b428::m125() {}

// 0x71009bbad8
void Unk_710247b428::m126() {
    auto* screen = sead::DynamicCast<ScreenControllerWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::ControllerWindow));
    if (!screen || screen->isOpened())
        mStateMachine.changeState(&sUnk_71025da040);
}

// 0x71009bbba0
void Unk_710247b428::m127() {}

// 0x71009bc084
s32 Unk_710247b428::m128() { return 0; }

// 0x71009bbba4
void Unk_710247b428::m129() {}

// 0x71009bbcb0
void Unk_710247b428::m131() {}

// 0x71009bc08c
s32 Unk_710247b428::m132() { return 0; }

// 0x71009bbcb4
void Unk_710247b428::m133() {}

// 0x71009bbcb8
void Unk_710247b428::m134() {
    auto* screen = sead::DynamicCast<ScreenDLCWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::DLCWindow));
    if (!screen || screen->isOpened())
        mStateMachine.changeState(&sUnk_71025da100);
}

// 0x71009bbd80
void Unk_710247b428::m135() {}

// 0x71009bc094
s32 Unk_710247b428::m136() { return 0; }

// 0x71009bbd84
void Unk_710247b428::m137() {}

// 0x71009bbd88
void Unk_710247b428::m138() {
    auto* screen = sead::DynamicCast<ScreenDLCWindow>(eui::ScreenMgr::instance()->getScreen(ScreenId::DLCWindow));
    if (!screen || screen->isClosed())
        mStateMachine.changeState(&sUnk_71025d9e00);
}

// 0x71009bbe50
void Unk_710247b428::m139() {}

// 0x71009bc09c
s32 Unk_710247b428::m140() { return 0; }

// 0x71009bbe54
void Unk_710247b428::m141() {}

// 0x71009bbe58
void Unk_710247b428::m142() {
    if (_1c8.sub_7100A83EC0())
        mStateMachine.changeState(&sUnk_71025d9e00);
}

// 0x71009bbe98
void Unk_710247b428::m143() {}

// 0x71009bc0a4
s32 Unk_710247b428::m144() { return 0; }

// 0x71009bbe9c
void Unk_710247b428::m145() {}

// 0x71009bbea0
void Unk_710247b428::m146() {
    auto* screen = sead::DynamicCast<ScreenSystemWindow00>(eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (!screen || screen->isOpened())
        mStateMachine.changeState(&sUnk_71025da220);
}

// 0x71009bbf68
void Unk_710247b428::m147() {}

// 0x71009bc0ac
s32 Unk_710247b428::m148() { return 0; }

// 0x71009bbf6c
void Unk_710247b428::m149() {}

// 0x71009bbf70
void Unk_710247b428::m150() {
    auto* screen = sead::DynamicCast<ScreenSystemWindow00>(eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
    if (!screen || screen->isClosed()) {
        mStateMachine.changeState(&sUnk_71025d9e00);
        return;
    }
    if (!sub_7100A64304())
        createTitleStageBinder(true, true);
}

// 0x71009bc054
void Unk_710247b428::m151() {}

// 0x71009bc0b4
s32 Unk_710247b428::m152() { return 0; }

// 0x71009ca1dc
void Unk_710247e468::m105() {}

// 0x71009ca2c8
void Unk_710247e468::m107() {}

// 0x71009ca2cc
void Unk_710247e468::m109() {
    if (_138)
        _138->Play(eui::Animator::PlayType(0), 1.0f);
}

// 0x71009ca340
void Unk_710247e468::m111() {
    _138->Play(eui::Animator::PlayType(0), -1.0f);
}

// 0x71009ca35c
s32 Unk_710247e468::m108() { return 0; }

// 0x71009ca364
s32 Unk_710247e468::m112() { return 0; }

}  // namespace uking::ui
