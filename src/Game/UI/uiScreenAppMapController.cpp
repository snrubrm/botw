#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"

namespace uking::ui {

// 0x71009c0ebc
ScreenAppMapUnk3c90::ScreenAppMapUnk3c90(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009c117c
void ScreenAppMapUnk3c90::sub_71009C117C() {
    _130 = 2;
    _134 = false;
    _140->StopAtMin();
}

// 0x71009c1198 (placeholder name): while _130 is 2, stops the _150 animation on the frame given by the type
void ScreenAppMapUnk3c90::sub_71009C1198(s32 type) {
    if (_130 == 2) {
        switch (type) {
        case 0:
            _150->Stop(0.0f);
            break;
        case 1:
            _150->Stop(1.0f);
            break;
        case 2:
            _150->Stop(2.0f);
            break;
        }
    }
    sub_71009C1218(0);
}

// 0x71009c1888 (placeholder name): for type 1, once the close animation has ended and _148 has reached
// frame 15, restarts the layout
void ScreenAppMapUnk3c90::sub_71009C1888(s32 type) {
    if (type != 1 || !_134 || !mLayout || !mLayout->isAnimCloseEnd(false))
        return;
    if (_148 && _148->mFrame >= 15.0f)
        mLayout->sub_7100BDDE7C(false, 0, true);
}

// 0x71009c18fc / 0x71009c1a5c: native forwarding hooks, callees remain undecompiled.
void ScreenAppMapUnk3c90::m24(sead::Heap*) {
    sub_71009C1900();
}

void ScreenAppMapUnk3c90::m31() {
    sub_71009C1080();
}

// 0x71009c1a60: the native repeats the small reset helper.
void ScreenAppMapUnk3c90::m34() {
    _130 = 2;
    _134 = false;
    _140->StopAtMin();
}

// 0x71009c1a7c
void ScreenAppMapUnk3c90::m27() {
    if (_130 == 2)
        return;
    mLayout->startAnimCloseImpl_(false, true);
}

// 0x71009c13d4 (placeholder name): for types 0 and 1, plays the open animations at normal speed
void ScreenAppMapUnk3c90::sub_71009C13D4(s32 type) {
    if (type == 1 || type == 0) {
        sub_71009C1530(_130);
        _138->PlayAuto(1.0f);
        _140->PlayAuto(1.0f);
        if (UiSubsys1::instance()->sub_7100960DAC(2))
            _158->PlayAuto(1.0f);
    }
}

// 0x71009c1474
void ScreenAppMapUnk3c90::sub_71009C1474(f32 speed, s32 type) {
    switch (type) {
    case 0:
        sub_71009C1530(_130);
        _138->PlayAuto(speed);
        _140->PlayAuto(speed);
        if (UiSubsys1::instance()->sub_7100960DAC(2))
            _158->PlayAuto(speed);
        break;
    case 1:
        _148->PlayAuto(speed);
        _134 = true;
        break;
    }
}

// 0x71009c1814
// NON_MATCHING: early-return branch layout.
bool ScreenAppMapUnk3c90::sub_71009C1814(s32 type) const {
    if (u32(_130) > 1)
        return true;
    switch (type) {
    case 0:
        return _138->mFrame == f32(_138->GetFrameSize());
    case 1:
        if (!_134)
            return false;
        return _148->mFrame == f32(_148->GetFrameSize());
    }
    return true;
}

// NON_MATCHING: the inlined ScreenChild member teardown differs in register allocation / scheduling only.
ScreenAppMapUnk3c90::~ScreenAppMapUnk3c90() = default;

}  // namespace uking::ui
