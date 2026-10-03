#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "AppSystemWindow_00";
}

// 0x71009fc4b8
const char* ScreenAppSystemWindow::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
