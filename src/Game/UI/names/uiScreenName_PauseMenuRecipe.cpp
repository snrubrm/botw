#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "PauseMenuRecipe_00";
}

// 0x7100a32970
const char* ScreenPauseMenuRecipe::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
