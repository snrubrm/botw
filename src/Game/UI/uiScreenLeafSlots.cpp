#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"

// Trivial state-callback slots (154 and up) of the leaf screens that declare their own virtuals.
namespace uking::ui {

// ScreenAppMap
// 0x71009ea178 (CSV ScreenAppMap::m92)
void ScreenAppMap::m92(sead::Heap*) {
    if (auto* subsys = UiSubsys1::instance())
        subsys->sub_710095B1BC();
}

// 0x71009ec18c (CSV ScreenAppMap::m100)
void ScreenAppMap::m100() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageTipsPauseMenu))
        screen->close(-1);
}

// 0x71009ebbfc (CSV ScreenAppMap::demoEnter)
void ScreenAppMap::demoEnter() {
    _3c00->StopAtMin();
    _3c08->StopAtMin();
    _3ad1 = 0;
    _3610->_b33a = 0;
    UiSubsys1::instance()->clear38c8();
    _3610->_b350 = 0;
}

// 0x71009ec01c (CSV ScreenAppMap::demoLeave)
void ScreenAppMap::demoLeave() {
    UiSubsys1::instance()->sub_7100968844();
    _3ad1 = 1;
}

// 0x71009eaf40 (CSV ScreenAppMap::m83)
void ScreenAppMap::m83() {
    sub_71009EACC0(0);
    mStateMachine.changeState(&sUnk_71025df180);
    if (_3638) {
        if (wm::isFindDungeonActivated())
            _3638->StopAtMin();
        else
            _3638->StopAtMax();
    }
    if (_3c88) {
        if (wm::sub_7100A9D800())
            _3c88->StopAtMax();
        else
            _3c88->StopAtMin();
    }
}

// 0x71009eb49c (CSV ScreenAppMap::mainEnter)
void ScreenAppMap::mainEnter() {
    _3ad1 = 1;
    _3610->_b33a = 1;
}

// 0x71009eb4b8 (CSV ScreenAppMap::mainRun)
void ScreenAppMap::mainRun() {
    if (UiSubsys1::instance()->is848EqualTo1())
        sub_71009EB52C();
    else if (UiSubsys1::instance()->is848Zero())
        sub_71009EB72C();
    if (sub_71009E9F48())
        mStateMachine.changeState(&sUnk_71025df1e0);
}

// 0x71009eb814 (CSV ScreenAppMap::subEnter)
void ScreenAppMap::subEnter() {
    _3c00->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    if (_3c98) {
        const s32 state = _3c98->_104;
        if (state == 7 || (u32(state - 1) <= 4 && ((state - 1) & 1) == 0))
            _3c08->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    }
    _3ad1 = 1;
    UiSubsys1::instance()->clear3885();
    _3610->_b350 = 0;
}

// 0x71009eb810 (CSV ScreenAppMap::mainLeave)
void ScreenAppMap::mainLeave() {}

// 0x71009ebbe0 (CSV ScreenAppMap::subLeave)
void ScreenAppMap::subLeave() {
    UiSubsys1::instance()->set3885();
}

// 0x71009f28b0
s32 ScreenAppMap::m157() {
    return 0;
}

// 0x71009f28b8
s32 ScreenAppMap::m161() {
    return 0;
}

// 0x71009f28c0 (CSV ScreenAppMap::demoReenter)
s32 ScreenAppMap::demoReenter() {
    return 0;
}

// ScreenAppPictureBook
// 0x71009faa9c
void ScreenAppPictureBook::m156() {
    if (_3658)
        _3658->sub_710093F594(false);
}

// 0x71009faccc
void ScreenAppPictureBook::m160() {
    if (_3660)
        _3660->sub_710093F594(false);
}

// 0x71009fa2f8
void ScreenAppPictureBook::m100() {
    if (_3658)
        _3658->sub_710093F594(false);
    if (_3660)
        _3660->sub_710093F594(false);
}

// ScreenAppCamera
// 0x71009db72c (CSV ScreenAppCamera::m99)
void ScreenAppCamera::m99() {
    mStateMachine.changeState(&sUnk_71025dcca0);
    ksys::gdt::setFlag_IsOpenAppCamera(true, false);
}

// 0x71009d9a28
void ScreenAppCamera::m163() {
    if (_3610 && _3610->_104)
        return;
    mStateMachine.changeState(&sUnk_71025dcca0);
}

// 0x71009d92e4
void ScreenAppCamera::m156() {}
// 0x71009d98b4
void ScreenAppCamera::m160() {}
// 0x71009dbd18
void ScreenAppCamera::m166() {}
// 0x71009dbd00
s32 ScreenAppCamera::m157() {
    return 0;
}
// 0x71009dbd08
s32 ScreenAppCamera::m161() {
    return 0;
}
// 0x71009dbd10
s32 ScreenAppCamera::m165() {
    return 0;
}

// ScreenAppMapDungeon
// 0x71009e33dc
void ScreenAppMapDungeon::m154() {}
// 0x71009e3a8c
void ScreenAppMapDungeon::m156() {}
// 0x71009e3a90
void ScreenAppMapDungeon::m158() {}
// 0x71009e3c90
void ScreenAppMapDungeon::m160() {}
// 0x71009e3c94
void ScreenAppMapDungeon::m162() {}
// 0x71009e3c98
void ScreenAppMapDungeon::m163() {}
// 0x71009e3c9c
void ScreenAppMapDungeon::m164() {}
// 0x71009e7de8
s32 ScreenAppMapDungeon::m157() {
    return 0;
}
// 0x71009e7df0
s32 ScreenAppMapDungeon::m161() {
    return 0;
}
// 0x71009e7df8
s32 ScreenAppMapDungeon::m165() {
    return 0;
}

// ScreenAppPictureBook
// 0x71009faecc
void ScreenAppPictureBook::m164() {}
// 0x71009fb208
s32 ScreenAppPictureBook::m157() {
    return 0;
}
// 0x71009fb210
s32 ScreenAppPictureBook::m161() {
    return 0;
}
// 0x71009fb218
s32 ScreenAppPictureBook::m165() {
    return 0;
}


// ScreenAppCamera creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102480388[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_SystemWindow_00", sub_71009D7294, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102480378(sUnk_7102480388);
// 0x71009d7168
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024803b8::getEntries() const {
    return &sUnk_7102480378;
}
// 0x71009d7174
Unk_71024803b8::~Unk_71024803b8() = default;

// ScreenAppMapDungeon creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102481048[] = {
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481038(sUnk_7102481048);
// 0x71009de3c4
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481078::getEntries() const {
    return &sUnk_7102481038;
}
// 0x71009de3d0
Unk_7102481078::~Unk_7102481078() = default;

}  // namespace uking::ui
