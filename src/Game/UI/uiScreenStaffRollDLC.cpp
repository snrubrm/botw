#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a56e60), merged into the block at 0x71025f4030 after
// the uiTUStatics.h objects. sub_7100A58480 passes the 5400 duration to ksys::Timer::hasEnded.
static f32 sUnk_71025F4048 = 5399.9995f;
static sead::SafeString sMessageSet = "LayoutMsg/StaffRollDLC_00";
static sead::SafeString sStaticSet = "StaticMsg/StaffRollDLC";

// 0x7100a58480
// NON_MATCHING: the original reads the 5400 duration from the TU's merged static block; our
// clang folds the constant-file static binding to a literal-pool load.
void ScreenStaffRollDLC::m94() {
    if (!isOpened() || _270 > 0.0f)
        return;
    if (!_3610.hasEnded(sUnk_71025F4048))
        _3610.update();
    sub_7100A58508(_3700, -_3688.y);
    sub_7100A58778(_3704);
    sub_7100A588EC();
}

}  // namespace uking::ui
