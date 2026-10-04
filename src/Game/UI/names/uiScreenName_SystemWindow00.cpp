#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "SystemWindow_00";
}

// 0x7100a6431c
const char* ScreenSystemWindow00::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
