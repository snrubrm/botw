#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ShopBtnList20_00";
}

// 0x7100a4bdb8
const char* ScreenShopBtnList20::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
