#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "KeyNum_00";
}

// 0x7100a0e7c8
const char* ScreenKeyNum::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
