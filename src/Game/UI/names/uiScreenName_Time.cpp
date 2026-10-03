#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "Time_00";
}

// 0x7100a68e84
const char* ScreenTime::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
