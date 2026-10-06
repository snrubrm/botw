#include "Game/UI/euiAnimator.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a16fd8
void ScreenMainScreenMS::sub_7100A16FD8() {
    if (_3610)
        _3610->PlayAuto(1.0f);
}

// 0x7100a16ff4
void ScreenMainScreenMS::sub_7100A16FF4() {
    if (_3610)
        _3610->PlayAuto(-1.0f);
}

}  // namespace uking::ui
