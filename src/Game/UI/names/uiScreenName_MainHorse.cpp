#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MainHorse_00";
}

// 0x7100a103c0
const char* ScreenMainHorse::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
