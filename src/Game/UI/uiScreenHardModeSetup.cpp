#include "Game/UI/euiAnimator.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a0bfc8
void ScreenHardMode::sub_7100A0BFC8(s32 index) {
    _3718 = -1;
    _3721 = 0;
    s32 old_index = _3700;
    _3700 = index;
    if (old_index != -1) {
        _3618->StopAtMax();
        _3620->PlayAuto(1.0f);
    } else {
        _3620->StopAtMax();
        if (_3700 != -1) {
            _3610->Stop(f32(_3700));
            _3618->PlayAuto(1.0f);
        }
    }
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

}  // namespace uking::ui
