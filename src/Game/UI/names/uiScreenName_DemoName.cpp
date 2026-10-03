#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "DemoName_00";
}

// 0x7100a03fc8
const char* ScreenDemoName::m15() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
