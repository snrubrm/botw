#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ShopInfo_00";
}

// 0x7100a51a64
const char* ScreenShopInfo::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
