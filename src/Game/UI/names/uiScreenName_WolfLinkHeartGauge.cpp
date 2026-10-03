#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "WolfLinkHeartGauge_00";
}

// 0x7100a6bc4c
const char* ScreenWolfLinkHeartGauge::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
