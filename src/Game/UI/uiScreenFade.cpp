#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiTagProcessor.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::ui {

// 0x71010a0a90
Fade::Fade() : Screen() {}

Fade::~Fade() = default;

// 0x71010a1ce0
bool Fade::isEnableControl() const {
    return true;
}

// 0x71010a0b3c
void Fade::open(s32 option) {
    Screen::open(option);
}

// 0x71010a0b40
void Fade::close(s32 option) {
    ksys::ui::callCloseFadeStatusScreen();
    Screen::close(option);
}

// 0x71010a1ce8
const char* Fade::getLayoutName_() const {
    return "Fade_00";
}

// 0x71010a1b64 (CSV Fade::m27)
eui::TagProcessor* Fade::doCreateTagProcessor_(sead::Heap* heap) {
    auto* processor = ScreenBase::doCreateTagProcessor_(heap);
    processor->setRubyEnabled(true);
    return processor;
}

// 0x71010a1b80
bool Fade::isOpenEnd_() {
    if (_a24)
        return true;
    if (eui::Screen::isOpenEnd_()) {
        _a24 = true;
        return false;
    }
    return false;
}

// 0x71010a0e20
void Fade::m74(f32 progress) {
    if (_a20 == -1 || _270 == 0)
        m76();

    const f32 duration = std::min(progress, _270);
    const f32 open_size = getOpenFrameSize();
    if (open_size == 0)
        return;

    const f32 ratio = duration / _270;
    f32 frame;
    switch (_a20) {
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

// 0x71010a0ee8
void Fade::sub_71010A0EE8(f32 progress) {
    _3b0 = progress;
}

// 0x71010a0bbc
void Fade::x(s32 forward) {
    if (forward)
        _300->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    else
        _300->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
}

// 0x71010a0b6c
void Fade::stopColorAnimatorAt(s32 where) {
    if (where)
        _300->StopAtMax();
    else
        _300->StopAtMin();
}

// 0x71010a0be8
void Fade::x_2() {
    if (!isClosed() && (_3a8 || !isOpened()))
        return;

    if (_3a8) {
        _308.select(1)->StopAtMin();
        eui::Animator* animator = _328.select(1);
        animator->nn::ui2d::AnimTransform::SetEnabled(false);
        animator->mRate = 0;
        mLayout->setOpenAnimator(_358);
        mLayout->setCloseAnimator(_360);
        mLayout->mOpenAnimator->Disable();
        mLayout->mCloseAnimator->Disable();
    } else {
        _358->StopAtMin();
        eui::Animator* animator = _360;
        animator->nn::ui2d::AnimTransform::SetEnabled(false);
        animator->mRate = 0;
        mLayout->setOpenAnimator(_308.select(_3ac));
        mLayout->mOpenAnimator->Disable();
        if (_3ac == 3) {
            mLayout->setCloseAnimator(nullptr);
        } else {
            mLayout->setCloseAnimator(_328.select(_3ac));
            mLayout->mCloseAnimator->Disable();
        }
        if (isOpened())
            mLayout->mOpenAnimator->StopAtMax();
    }
}

// 0x71010a0be0
void Fade::x_1(s32 type) {
    _3ac = type;
    x_2();
}

// 0x71010a0d34
void Fade::setStartedMaybe(bool started) {
    _3a8 = started;
    x_2();
}

// 0x71010a0d40
void Fade::clearSomeTipsField() {
    mTips.clear();
}

}  // namespace uking::ui
