#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MessageTipsPauseMenu_00";
}

// 0x7100a25d48
const char* ScreenMessageTipsPauseMenu::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
