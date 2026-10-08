#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiManager.h"
#include "Game/gameGraphics.h"
#include "KingSystem/System/DebugBoard.h"

// Slots that forward to open() / close() with a constant argument.
namespace uking::ui {

// 0x7100a0b1c4
void ScreenGamePadBG::m82() {
    open(1);
}

// NON_MATCHING: the original materialises !isOpened() (eor) before testing it; branch layout of the last select.
// 0x7100a0b1d8
void ScreenGamePadBG::m83() {
    open(3);
    const s32 type = DebugBoardMgr::instance()->_39bc;
    if (type == 0) {
        if (_3618)
            _3618->StopAtMin();
    } else if (type == 1) {
        if (_3618)
            _3618->StopAtMax();
    }
    if (!_3620)
        return;
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::KeyBoradTextArea)) {
        const bool opened = screen->isOpened();
        if ((_292 & 0x40) && !opened)
            _3620->StopAtMin();
        else
            _3620->StopAtMax();
    } else if (_292 & 0x40) {
        _3620->StopAtMin();
    } else {
        _3620->StopAtMax();
    }
}

// 0x7100a0b140
void ScreenGamePadBG::m93(sead::Heap*) {
    _3610 = mButtonHelper.sub_71009301F4(0);
    _3618 = mLayout->tryCreateAnimatorAuto("Type", false);
    if (_3618)
        _3618->StopAtMin();
    _3620 = mLayout->tryCreateAnimatorAuto("Mode", false);
    if (_3620)
        _3620->StopAtMin();
}

// 0x7100a11ed4
void ScreenMainScreen3D::m84() {
    open(1);
}

// 0x7100a2bedc
void ScreenPauseMenuBG::sub_7100A2BEDC() {
    if (mLayout->_91 == 3 || mLayout->_91 == 0) {
        mLayout->sub_7100BDDE7C(false, 1, true);
        const u64 flags = Manager::instance()->_64c30;
        _3610 = (flags >> 1) & 1;
        if (flags & 2)
            Graphics::instance()->sub_7100F35FA4(true, true);
    }
}

// 0x7100a2bf64
void ScreenPauseMenuBG::sub_7100A2BF64() {
    if (static_cast<u32>(mLayout->_91 - 1) <= 1) {
        mLayout->startAnimCloseImpl_(false, true);
        if (_3610) {
            Graphics::instance()->sub_7100F35FA4(false, true);
            _3610 = 0;
        }
    }
}

// 0x7100a2bea8
void ScreenPauseMenuBG::m82() {
    open(4);
}

// 0x7100a2beb8
void ScreenPauseMenuBG::m83() {
    open(4);
}

// 0x7100a4aa20
void ScreenSeekPadMenuBG::m82() {
    open(4);
}

// 0x7100a4aa30
void ScreenSeekPadMenuBG::m83() {
    open(4);
}

// 0x7100a2c2b0
void ScreenPauseMenuEiketsu::m107(eui::AnimButton*) {
    close(-1);
}

}  // namespace uking::ui
