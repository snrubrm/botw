#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ShopBtnList5_00";
}

// 0x7100a4dac0
const char* ScreenShopBtnList5::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
