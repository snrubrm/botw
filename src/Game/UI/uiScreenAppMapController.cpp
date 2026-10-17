#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"

namespace uking::ui {

// 0x71025db000: the map controller's static data block; its animator name buffer is at +0x148
struct Unk_71025db000 {
    u8 _0[0x148];
    /* 0x148 */ sead::Buffer<sead::SafeString> mAnimatorNames;
};
KSYS_VISIBILITY_HIDDEN Unk_71025db000 sUnk_71025db000;

// 0x71025daf90: the widget the map controller's name text goes into
KSYS_VISIBILITY_HIDDEN sead::SafeString sUnk_71025daf90;

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

// 0x71009c107c
void ScreenAppMapUnk3c90::sub_71009C107C() {
    sub_71009C1080();
}

// 0x71009c1080
void ScreenAppMapUnk3c90::sub_71009C1080() {
    sub_71009C1218(0);
    if (_130 != 2)
        return;
    if (mLayout) {
        if (UiSubsys1::instance()->get38a4() == -1)
            mLayout->startAnimCloseImpl_(false, true);
        else
            mLayout->sub_7100BDDE7C(false, 1, true);
    }
    const s32 state = UiSubsys1::instance()->get38a8();
    switch (state) {
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
    _138->StopAtMin();
    _158->StopAtMin();
}

// 0x71009c1218
void ScreenAppMapUnk3c90::sub_71009C1218(s32 type) {
    if (type != 0)
        return;
    if (UiSubsys1::instance()->get38a8() != 1)
        return;
    sead::FixedSafeString<64> name;
    UiSubsys1::instance()->sub_7100960758(&name);
    eui::MessageString message;
    sub_7100AA2BDC(name, &message);
    setWidgetString(mLayout, sUnk_71025daf90, message);
}

// 0x71009c1900
void ScreenAppMapUnk3c90::sub_71009C1900() {
    if (!mLayout)
        return;
    _138 = mLayout->createAnimatorAuto(sUnk_71025db000.mAnimatorNames[0].cstr(), false);
    if (!mLayout)
        return;
    _140 = mLayout->createAnimatorAuto(sUnk_71025db000.mAnimatorNames[1].cstr(), false);
    if (!mLayout)
        return;
    _148 = mLayout->createAnimatorAuto(sUnk_71025db000.mAnimatorNames[2].cstr(), false);
    if (!mLayout)
        return;
    _150 = mLayout->createAnimatorAuto(sUnk_71025db000.mAnimatorNames[3].cstr(), false);
    if (!mLayout)
        return;
    _158 = mLayout->createAnimatorAuto(sUnk_71025db000.mAnimatorNames[4].cstr(), false);
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
