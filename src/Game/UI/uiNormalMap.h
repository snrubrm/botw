#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiUnkTiny.h"

namespace ksys::res {
class Handle;
}
namespace nn::ui2d {
class Material;
}
namespace eui {
class LayoutEx;
}

namespace uking::ui {

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

    /* 0x08 */ s32 mType = -1;
    u8 _c[4];
    /* 0x10 */ Unk_7102479bd0 mTexture;
    /* 0x88 */ bool _88 = true;
    /* 0x89 */ bool _89 = true;
    /* 0x8a */ u16 _8a = 0;
    /* 0x8c */ s32 _8c = -1;
    /* 0x90 */ eui::LayoutEx* mLayout = nullptr;
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

    u8 _8[0x28 - 8];
    /* 0x28 */ Unk_7102479bb0 mEntries[120];
    /* 0x12e8 */ Unk_7102479bf0 mTiles[240];
    u8 _a8e8[0xaa48 - 0xa8e8];
};
static_assert(sizeof(Unk_7102479c10) == 0xaa48);

}  // namespace uking::ui
