#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "KeyBoradTextArea_00";
}

// 0x7100a0e57c
const char* ScreenKeyBoradTextArea::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
