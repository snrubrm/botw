#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "PauseMenuMantan_00";
}

// 0x7100a321b4
const char* ScreenPauseMenuMantan::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
