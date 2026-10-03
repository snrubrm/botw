#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ShopBG_00";
}

// 0x7100a4abec
const char* ScreenShopBG::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
