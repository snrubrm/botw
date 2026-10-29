#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <nn/ui2d/TextureInfo.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiTimer.h"
#include "Game/UI/uiUnkTiny.h"

namespace sead {
class Color4f;
}

namespace ksys::res {
class Handle;
}
namespace nn::ui2d {
class Material;
class Pane;
}
namespace eui {
class LayoutEx;
}

namespace uking::ui {

class UiSubsys1;

// Clamps a map-space position to the map extent and scales it to UI units (the sequence repeated by
// the debug drawing helpers 9A82B4 / 9A8460). Inline-only in the original; name is a guess.
inline sead::Vector2f clampMapPosition(sead::Vector2f position) {
    position.x = sead::Mathf::clamp(position.x, -50000.0f, 50000.0f);
    position.y = sead::Mathf::clamp(position.y, -50000.0f, 50000.0f);
    position.x *= 0.03448276f;
    position.y *= 0.03448276f;
    return position;
}

// Texture loader embedded at +0x10 of each 0xa0-byte map tile (9A5930 / 9A62C0).
class Unk_7102479bd0 {
public:
    virtual ~Unk_7102479bd0();

    /* 0x08 */ ksys::res::Handle* mHandle = nullptr;
    /* 0x10 */ nn::ui2d::Material* mMaterial = nullptr;
    /* 0x18 */ s32 mState = -1;
    /* 0x1c */ s32 mIndex = -1;
    /* 0x20 */ sead::FixedSafeString<64> mPath;
};
static_assert(sizeof(Unk_7102479bd0) == 0x78);

// Native 9A5930 initializes 240 tile records; 9A62C0 supplies the layout and handle.
class Unk_7102479bf0 {
public:
    virtual ~Unk_7102479bf0();
    // 0x71009a55a0: advances a completed texture request, or prepares its path for another request.
    void sub_71009A55A0(u32 level);
    // 0x71009a524c (CSV unnamed; not decompiled)
    void sub_71009A524C();

    /* 0x08 */ s32 mType = -1;
    u8 _c[4];
    /* 0x10 */ Unk_7102479bd0 mTexture;
    /* 0x88 */ bool _88 = true;   // the pane is fully shown
    /* 0x89 */ bool _89 = true;   // previous _88
    /* 0x8a */ bool _8a = false;  // the pane is hidden
    /* 0x8b */ bool _8b = false;  // previous _8a
    /* 0x8c */ s32 _8c = -1;      // fade mode (0: in, 1: shown, 2: out, 3: hidden)
    /* 0x90 */ nn::ui2d::Pane* mPane = nullptr;
    /* 0x98 */ Unk_7102479bb0* mMapEntry = nullptr;
};
static_assert(sizeof(Unk_7102479bf0) == 0xa0);

// Native 9A5670 accepts a nullable map entry and writes its texture path.
void sub_71009A5670(const Unk_7102479bb0* entry, u32 level, sead::BufferedSafeString* path);

// Embedded at ScreenAppMapWidget +0x8f0; its next field starts at +0xb338 (9A863C).
// Native 9A5930 owns 120 map entries and 240 texture tiles; 9A5BC8 destroys the tiles.
class Unk_7102479c10 {
public:
    virtual ~Unk_7102479c10();
    // 0x71009a63f4 / 0x71009a6f34 (CSV unnamed; not decompiled): called by ScreenAppMapWidget::m31 / m21
    void sub_71009A63F4();
    // 0x71009a64e0 / 0x71009a6ff4 / 0x71009a75ac (placeholder names; not decompiled): called by sub_71009A63F4
    void sub_71009A64E0();
    // 0x71009a7cf0 / 0x71009a80d0: queue tile textures for all areas / one area.
    void sub_71009A7CF0();
    void sub_71009A80D0(s32 mode, s32 area);
    void sub_71009A6FF4();
    void sub_71009A75AC();
    void sub_71009A6F34();
    // 0x71009a7fa4 (declared only; 300 bytes): resets the normal map tiles' state when the UI mode allows it
    void sub_71009A7FA4();
    // 0x71009a61dc (placeholder name): sizes the map view (_10) from the first tile pane
    void sub_71009A61DC();
    // 0x71009a82a8: the byte at 0xa8ea (ScreenAppMap has loaded the normal map)
    bool sub_71009A82A8() const;
    // 0x71009a829c: the byte at 0xa8e9 (the demo state's normal map ready flag)
    bool sub_71009A829C() const;
    // 0x71009a5cfc (declared only; 780 bytes): builds the map entries and tiles from the panes of `arg`
    void sub_71009A5CFC(const Unk_7102479fb0& arg, sead::Heap* heap);
    // 0x71009a82b4 (placeholder name): draws `bounds` on the map screen, inset by one unit per repeat
    void sub_71009A82B4(const sead::BoundBox2f& bounds, const sead::Color4f& color, s32 count, bool a4,
                        bool a5, bool a6);
    // 0x71009a8460 (placeholder name): draws a quad's clamped corners on the map screen; the parameter
    // before the flags is never read (a guess, the original's caller passes it as an undef register)
    void sub_71009A8460(f32 size, const sead::Vector2f& corner0, const sead::Vector2f& corner1,
                        const sead::Vector2f& corner2, const sead::Vector2f& corner3,
                        const sead::Color4f& color, bool a7, bool show_corners, bool show_center,
                        bool flag, const sead::Vector2f& offset);

    /* 0x08 */ UiSubsys1* _8 = nullptr;  // the UI subsystem (its _128 is the current map area)
    /* 0x10 */ Unk_71024753a8* _10;
    u8 _18[0x28 - 0x18];
    /* 0x28 */ Unk_7102479bb0 mEntries[120];
    // 9A8224..9A822C retains the fixed-array bound check and index-zero fallback.
    /* 0x12e8 */ sead::SafeArray<Unk_7102479bf0, 240> mTiles;
    /* 0xa8e8 */ u8 _a8e8;
    /* 0xa8e9 */ bool _a8e9;  // returned by sub_71009A829C
    /* 0xa8ea */ bool _a8ea;  // returned by sub_71009A82A8
    /* 0xa8eb */ u8 _a8eb;  // ScreenAppMapWidget::sub_71009A9438 / sub_71009AF37C read it
    u8 _a8ec[0xa8f0 - 0xa8ec];
    // the texture the tiles show while unloaded (sub_71009A6F34)
    /* 0xa8f0 */ nn::ui2d::ExternalTextureInfo _a8f0;
    u8 _a908[0xa9a0 - 0xa908];
    /* 0xa9a0 */ UiTimer _a9a0;
    u8 _a9b8[0xa9e0 - 0xa9b8];
    /* 0xa9e0 */ nn::ui2d::Pane* _a9e0;
    /* 0xa9e8 */ nn::ui2d::Pane* _a9e8;
    /* 0xa9f0 */ nn::ui2d::Pane** _a9f0;
    u8 _a9f8[0xaa48 - 0xa9f8];
};
static_assert(sizeof(Unk_7102479c10) == 0xaa48);

}  // namespace uking::ui
