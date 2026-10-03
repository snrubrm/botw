#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "SystemWindowNoBtn_00";
}

// 0x7100a60494
const char* ScreenSystemWindowNoBtn::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
