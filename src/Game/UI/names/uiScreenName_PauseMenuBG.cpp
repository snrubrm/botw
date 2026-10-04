#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "PauseMenuBG_00";
}

// 0x7100a2be64
const char* ScreenPauseMenuBG::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
