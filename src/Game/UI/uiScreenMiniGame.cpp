#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

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
