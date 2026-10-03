#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ChangeController_00";
}

// 0x7100a00e40
const char* ScreenChangeController::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
