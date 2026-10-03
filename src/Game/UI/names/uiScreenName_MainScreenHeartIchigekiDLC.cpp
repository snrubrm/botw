#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MainScreenHeartIchigekiDLC_00";
}

// 0x7100a167f4
const char* ScreenMainScreenHeartIchigekiDLC::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
