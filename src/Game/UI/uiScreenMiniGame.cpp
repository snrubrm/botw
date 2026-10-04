#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a2745c
bool ScreenMiniGame::openMinigameScreen(s32 index, s32) {
    _3650 |= 1 << index;
    return sub_7100A2747C(index, false);
}

// 0x7100a275ec
bool ScreenMiniGame::sub_7100A275EC(s32 index, s32) {
    _3650 &= ~(1 << index);
    if (u32(index) > 6)
        return false;
    eui::LayoutEx* layout = _3610[index];
    if (!layout)
        return false;
    if (layout->_91 == 2)
        layout->startAnimCloseImpl_(false, false);
    return true;
}

// 0x7100a28088
void ScreenMiniGame::sub_7100A28088() {
    if (_3648)
        _3648->PlayAuto(1.0f);
}

// 0x7100a283b0
void ScreenMiniGame::sub_7100A283B0(s32 a1) {
    if (!_36e0)
        return;
    u16 size = _36e0->GetFrameSize();
    f32 frame = 0.0f;
    if (a1 >= 0) {
        frame = a1;
        if (frame > f32(size))
            frame = f32(size);
    }
    _36e0->Stop(frame);
}

// NON_MATCHING: same logic; the original keeps the two comparisons as separate branches (and loads the vtable slot
// before them), clang merges them into fccmp + csel
// 0x7100a28418
void ScreenMiniGame::sub_7100A28418(s32 a1) {
    if (!_36e8)
        return;
    u16 size = _36e8->GetFrameSize();
    f32 frame = 0.0f;
    if (a1 >= 0) {
        frame = a1;
        if (frame > f32(size))
            frame = f32(size);
    }
    _36e8->Stop(frame);
    invokeSoundLink2Event_(frame > sead::Mathf::epsilon() || frame < -sead::Mathf::epsilon() ? "mc_ChallengeFailed" :
                                                                                               "mc_NewRecord");
}

}  // namespace uking::ui
