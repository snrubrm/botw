#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "OPtext_00";
}

// 0x7100a2870c
const char* ScreenOPtext::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
