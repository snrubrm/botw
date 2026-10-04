#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "AppSystemWindowNoBtn_00";
}

// 0x71009fb8fc
const char* ScreenAppSystemWindowNoBtn::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
