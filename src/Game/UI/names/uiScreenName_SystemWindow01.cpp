#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "SystemWindow_01";
}

// 0x7100a67138
const char* ScreenSystemWindow01::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
