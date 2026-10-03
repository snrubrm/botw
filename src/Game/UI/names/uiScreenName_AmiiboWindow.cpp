#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "AmiiboWindow_00";
}

// 0x71009d0c50
const char* ScreenAmiiboWindow::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
