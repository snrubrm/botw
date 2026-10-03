#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "End_00";
}

// 0x7100a08464
const char* ScreenEnd::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
