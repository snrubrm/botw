#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "LoadingWeapon_00";
}

// 0x7100a0fd50
const char* ScreenLoadingWeapon::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
