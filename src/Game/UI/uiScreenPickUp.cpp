#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a406dc). The FixedSafeString sits on its own at 0x71025f1838
// (only the static initializer touches it); the layout name is merged into the block at 0x71025f18e0 after
// the uiTUStatics.h objects.
static sead::FixedSafeString<128> sUnk_71025F1838;
static sead::SafeString sLayoutName = "PickUpWin_00";

// 0x7100a3f768
const char* ScreenPickUp::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
