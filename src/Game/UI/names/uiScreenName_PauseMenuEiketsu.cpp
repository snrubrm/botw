#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "PauseMenuEiketsu_00";
}

// 0x7100a2c178
const char* ScreenPauseMenuEiketsu::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
