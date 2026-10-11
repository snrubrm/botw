#include <algorithm>
#include "KingSystem/Sound/sndMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x71010a0138
ScreenFadeDemo::ScreenFadeDemo() : Screen() {}

// 0x71010a01a8
void ScreenFadeDemo::sub_71010A01A8(s32 where) {
    if (where)
        _300->StopAtMax();
    else
        _300->StopAtMin();
}

// 0x71010a01c4
bool ScreenFadeDemo::sub_71010A01C4() {
    return _300->mFrame == f32(_300->GetFrameSize());
}

// 0x71010a060c (the same code as Fade::isOpenEnd_, with the flag at 0x358)
bool ScreenFadeDemo::isOpenEnd_() {
    if (_358)
        return true;
    if (eui::Screen::isOpenEnd_()) {
        _358 = true;
        return false;
    }
    return false;
}

// 0x71010a0534
void ScreenFadeDemo::m98() {
    _358 = false;
    ksys::snd::SoundMgr::instance()->sub_71011FC0C0(sub_71010A0DE0(false, mLayout->_91 == 2, _350), 1);
    UI::instance()->sub_71010A7994(true);
}

// 0x71010a059c
void ScreenFadeDemo::m100() {
    ksys::snd::SoundMgr::instance()->sub_71011FC17C(sub_71010A0DE0(false, mLayout->_91 == 0, _350), 1);
    UI::instance()->sub_71010A7994(false);
}

// 0x71010a05fc
void ScreenFadeDemo::m101() {
    ksys::snd::SoundMgr::instance()->sub_71011FC288();
}

// 0x71010a02f0 (the same code as Fade::m74, with the state at 0x354)
void ScreenFadeDemo::m74(f32 progress) {
    if (_354 == -1 || _270 == 0)
        m76();

    const f32 duration = std::min(progress, _270);
    const f32 open_size = getOpenFrameSize();
    if (open_size == 0)
        return;

    const f32 ratio = duration / _270;
    f32 frame;
    switch (_354) {
    case 0:
        frame = open_size - open_size * ratio;
        break;
    case 1:
        frame = open_size * ratio;
        break;
    default:
        frame = 0;
        break;
    }
    open(1);
    sub_7100BE9DD4(frame);
}

void ScreenFadeDemo::sub_71010A0200() {
    if (!isClosed() && !isOpened())
        return;
    if (_350 == 3) {
        _308.mCurrent->StopAtMin();
        if (isOpened())
            _348->StopAtMax();
        else
            _348->StopAtMin();
        mLayout->mOpenAnimator = _348;
        mLayout->mCloseAnimator = nullptr;
    } else {
        _348->StopAtMin();
        _308.select(_350);
        _328.select(_350);
        if (isOpened())
            _308.mCurrent->StopAtMax();
        else
            _308.mCurrent->StopAtMin();
        mLayout->mOpenAnimator = _308.mCurrent;
        mLayout->mCloseAnimator = _328.mCurrent;
    }
}

void ScreenFadeDemo::sub_71010A01F8(s32 value) {
    _350 = value;
    sub_71010A0200();
}

ScreenFadeDemo::~ScreenFadeDemo() = default;

// 0x71010a076c
const char* ScreenFadeDemo::getLayoutName_() const {
    return "FadeDemo_00";
}

}  // namespace uking::ui
