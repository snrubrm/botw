#include "KingSystem/AOC/aocManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

// The accessors below read the widget's zoom / cursor state (offsets 0xb4a0-0xb4ff).

// 0x71009a9438
bool ScreenAppMapWidget::sub_71009A9438() {
    return mNormalMap._a9a0.isDone() || mNormalMap._a8eb;
}

// 0x71009a995c
void ScreenAppMapWidget::sub_71009A995C() {
    _b34c = 1;
}

// 0x71009aef7c
s32 ScreenAppMapWidget::sub_71009AEF7C() const {
    return _b4a0;
}

// 0x71009aefec
sead::Vector2f ScreenAppMapWidget::sub_71009AEFEC() const {
    return {(_b4b8 + _b4b8) * _b4e8 + _b4e0, _b4bc * -2.0f * _b4e8 + _b4e4};
}

// 0x71009af0b4
bool ScreenAppMapWidget::sub_71009AF0B4() const {
    return (_b4ff >> 4) & 1;
}

// 0x71009af0c4
bool ScreenAppMapWidget::sub_71009AF0C4() const {
    return _b4a8 == 1;
}

// 0x71009af0d8
bool ScreenAppMapWidget::sub_71009AF0D8() const {
    return _b4a8 == 2;
}

// 0x71009af0ec
bool ScreenAppMapWidget::sub_71009AF0EC() const {
    return (_b4ff >> 5) & 1;
}

// 0x71009af0fc
bool ScreenAppMapWidget::sub_71009AF0FC() const {
    return _b4fe > 0;
}

// 0x71009af110
bool ScreenAppMapWidget::sub_71009AF110() const {
    return s8(_b4ff) < 0;
}

// 0x71009af124
void ScreenAppMapWidget::sub_71009AF124(sead::Vector2f* out) const {
    out->x = (_b4b0 + _b4b0) * _b4e8 + _b4e0;
    out->y = _b4b4 * -2.0f * _b4e8 + _b4e4;
}

// 0x71009af178
// NON_MATCHING: same result; the original keeps the branch (`tbnz` / `ubfx`), ours selects with `csinc`
u8 ScreenAppMapWidget::sub_71009AF178() const {
    if (!(_b4ff & 1))
        return 1;
    return (_b4ff >> 1) & 1;
}

// 0x71009af194
bool ScreenAppMapWidget::sub_71009AF194() const {
    return (_b4ff & 5) == 5;
}

// 0x71009a9b48
void ScreenAppMapWidget::sub_71009A9B48() {
    UiSubsys1::instance()->sub_7100966894();
    _b350 = 0;
}

// 0x71009a9b7c
void ScreenAppMapWidget::sub_71009A9B7C() {
    _b350 = 1;
    sub_71009A9B8C();
}

// 0x71009a9e74
void ScreenAppMapWidget::sub_71009A9E74(const sead::Vector3f* pos) {
    _b350 = 2;
    UiSubsys1::instance()->sub_7100966684(pos);
}

// 0x71009aa004
void ScreenAppMapWidget::sub_71009AA004() {
    if (ksys::aoc::Manager::instance()->getVersion() >= 0x200)
        sub_71009AA024();
}

// 0x71009af034
f32 ScreenAppMapWidget::sub_71009AF034() const {
    static const sead::SafeArray<f32, 32> sTable{{0.0625f, 0.25f, 0.5625f, 1.0f, 1.5625f, 2.25f, 3.0625f, 4.0f, 5.0625f,
                                                  6.25f, 7.5625f, 9.0f, 10.5625f, 12.25f, 14.0625f, 16.0f, 17.9375f,
                                                  19.75f, 21.4375f, 23.0f, 24.4375f, 25.75f, 26.9375f, 28.0f,
                                                  28.9375f, 29.75f, 30.4375f, 31.0f, 31.4375f, 31.75f, 31.9375f,
                                                  32.0f}};
    return sTable[_b4fc];
}

// NON_MATCHING: the original adds `_b388 + _b499` as `add w8, w8, w9`; ours emits the operands swapped (`add w8, w9, w8`)
// 0x71009aef88
void ScreenAppMapWidget::sub_71009AEF88() {
    _b4ec = 0;
    _b4f0 = 0;
    if (_b388 + _b499 >= 1) {
        const u32 packed = *_b370;
        s32 x = (packed >> 13) & 0x1fff;
        if (packed & 0x4000000)
            x = -x;
        s32 y = packed & 0xfff;
        if (packed & 0x1000)
            y = -y;
        _b4b8 = f32(x);
        _b4bc = f32(y);
    }
}

KSYS_VISIBILITY_HIDDEN bool sUnk_71025D9610 = false;

// 0x71009ae04c
void ScreenAppMapWidget::setMode(s32 mode) {
    _b4a0 = mode;

    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome))) {
        home->sub_71009DC99C(false);
        home->x_2();
    }

    if (UiSubsys1::instance()->get38b8())
        return;

    switch (mode) {
    case 0:
        UiSubsys1::instance()->set38c8();
        _b4ff &= 0xf;
        _b4a8 = 0;
        _b4fd = 0;
        sUnk_71025D9610 = true;
        break;
    case 1:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        _b4ac = 0;
        break;
    case 2:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        break;
    case 3:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        break;
    }
}

// 0x71009a8be8
void ScreenAppMapWidget::m14() {
    for (s32 i = 120; i < 240; ++i)
        mNormalMap.mTiles[i].mTexture.mState = 1;
    mNormalMap._a9a0.reset();
}

// 0x71009a9380
void ScreenAppMapWidget::m21() {
    mNormalMap.sub_71009A6F34();
}

// 0x71009a9280
void ScreenAppMapWidget::m31() {
    UiSubsys1::instance()->sub_710095B530();
    if (_8e8)
        mNormalMap.sub_71009A63F4();
    _8e8 = false;
}

// 0x71009af37c
u8 ScreenAppMapWidget::sub_71009AF37C() const {
    return mNormalMap._a8eb;
}

ScreenAppMapWidget::~ScreenAppMapWidget() = default;

}  // namespace uking::ui
