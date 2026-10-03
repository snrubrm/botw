#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "Skip_00";
}

// 0x7100a53680
const char* ScreenSkip::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
