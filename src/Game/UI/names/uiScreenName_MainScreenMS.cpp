#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MainScreenMS_00";
}

// 0x7100a16cf0
const char* ScreenMainScreenMS::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
