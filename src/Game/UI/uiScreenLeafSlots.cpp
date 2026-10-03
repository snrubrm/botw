#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

// Trivial state-callback slots (154 and up) of the leaf screens that declare their own virtuals.
namespace uking::ui {

// ScreenAppMap
// 0x71009ea178 (CSV ScreenAppMap::m92)
void ScreenAppMap::m92() {
    if (auto* subsys = UiSubsys1::instance())
        subsys->sub_710095B1BC();
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
