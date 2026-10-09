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

}  // namespace uking::ui
