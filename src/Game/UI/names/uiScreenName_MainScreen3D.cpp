#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MainScreen3D_00";
}

// 0x7100a11d88
const char* ScreenMainScreen3D::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
