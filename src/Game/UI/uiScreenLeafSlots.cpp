#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

// Trivial state-callback slots (154 and up) of the leaf screens that declare their own virtuals.
namespace uking::ui {

// ScreenAppMap
// 0x71009ea178 (CSV ScreenAppMap::m92)
void ScreenAppMap::m92(sead::Heap*) {
    if (auto* subsys = UiSubsys1::instance())
        subsys->sub_710095B1BC();
}

// 0x71009eb49c (CSV ScreenAppMap::mainEnter)
void ScreenAppMap::mainEnter() {
    _3ad1 = 1;
    _3610->_b33a = 1;
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

// ScreenAppCamera
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

}  // namespace uking::ui
