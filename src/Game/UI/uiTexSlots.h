#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class Handle;
}

namespace eui {
class Animator;
}

namespace uking::ui {

// Stand-ins for the parts of nn::ui2d::Material that are used (lib/NintendoSDK declares no data members): `texMaps` is
// the material's array of texture map slots (16 bytes each; the second word is the texture info pointer).
struct TexMapSlot {
    void* _0;
    const void* textureInfo;
};

struct TexMaterial {
    u8 _0[0x18];
    TexMapSlot* texMaps;
};

// Polymorphic texture info object embedded in UiTexSlots (vtable 0x2477bd8; it is what a material's texture map slot
// points to while no texture is loaded). The class name and the virtual functions are not known.
class UiTexInfo {
public:
    virtual ~UiTexInfo() = default;

    u64 _8 = u64(-1);
    u32 _10 = 0;
};
static_assert(sizeof(UiTexInfo) == 0x18);

// Member of ShopBtnList15 / ShopInfo / AppTool / AppMap / MainShortCut / StaffRoll(DLC) (vtable 0x249ce30; the class
// name is not known). Loads a texture resource per entry (the resource's texture is attached to the material's texture
// map slot while it is loaded, a default texture info (`mTexInfo`) otherwise) and plays an optional animator.
// Only construction / destruction / unloading are decompiled so far.
class UiTexSlots {
public:
    struct Entry {
        ksys::res::Handle* handle;
        TexMaterial* material;
        s32 texMapIndex;
        bool loaded;
        eui::Animator* animator;
    };
    static_assert(sizeof(Entry) == 0x20);

    // 0x7100a81208
    UiTexSlots();
    virtual ~UiTexSlots();

    // 0x7100a813e0
    void unload(s32 index);

private:
    /* 0x08 */ sead::Buffer<Entry> mEntries;
    /* 0x18 */ UiTexInfo mTexInfo;
    /* 0x30 */ s32 mMode = 0;
    /* 0x34 */ u8 _34[4];
    /* 0x38 */ sead::FixedSafeString<128> mPath;
};
static_assert(sizeof(UiTexSlots) == 0xd0);

}  // namespace uking::ui
