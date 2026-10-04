#include "Game/UI/uiScreens.h"

// Small leaf screen methods (named after their CSV address).
namespace uking::ui {

// 0x7100a0772c
void ScreenDoCommand::sub_7100A0772C(s32 a1) {
    _365c = a1;
}

// 0x7100a349f4
bool ScreenPauseMenu::sub_7100A349F4() {
    return _3bb4 == 3;
}

// 0x7100a34a10
bool ScreenPauseMenu::sub_7100A34A10() {
    return _3bb4 != 0;
}

// 0x7100a26db8
void ScreenMessageTipsRunTime::m101() {
    if (_3684 == -1)
        _3660 = -1;
}

}  // namespace uking::ui
