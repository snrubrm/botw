#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <nn/ui2d/Material.h>
#include <nn/ui2d/TextureInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class Handle;
}

namespace eui {
class Animator;
class LayoutEx;
}

namespace uking::ui {

// Member of ShopBtnList15 / ShopInfo / AppTool / AppMap / MainShortCut / StaffRoll(DLC) (vtable 0x249ce30; the class
// name is not known). Loads a texture resource per entry (the resource's texture is attached to the material's texture
// map slot while it is loaded, a default texture info (`mTexInfo`) otherwise) and plays an optional animator.
// Only construction / destruction / unloading are decompiled so far.
class UiTexSlots {
public:
    struct Entry {
        ksys::res::Handle* handle;
        nn::ui2d::Material* material;
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

    // 0x7100a819fc / 0x7100a81a30 / 0x7100a81a7c (placeholder names): store the material of entry `index` (and its texture
    // map index) and optionally attach the default texture info of the first texture map / re-apply it
    void setMaterial(s32 index, nn::ui2d::Material* material, bool apply);
    void setMaterialAndTexMapIndex(s32 index, nn::ui2d::Material* material, s32 tex_map_index, bool apply);
    void applyMaterial(s32 index);
    // 0x7100a81aac: creates the entry's animator `name` of `layout`
    void setAnimator(s32 index, eui::LayoutEx* layout, const sead::SafeString& name);
    // 0x7100a81f14
    bool isLoaded(s32 index);
    // 0x7100a816d8 (804 bytes, declared only; lane2 s46): called by the shop screens' slot 94
    void sub_7100A816D8();

private:
    /* 0x08 */ sead::Buffer<Entry> mEntries;
    /* 0x18 */ nn::ui2d::ExternalTextureInfo mTexInfo;
    /* 0x30 */ s32 mMode = 0;
    /* 0x34 */ u8 _34[4];
    /* 0x38 */ sead::FixedSafeString<128> mPath;
};
static_assert(sizeof(UiTexSlots) == 0xd0);

// vtable 0x7102481e30 (only the destructors): a holder of one UiTexSlots (ScreenAppMap's own member; the name is a
// placeholder).
class Unk_7102481e30 {
public:
    virtual ~Unk_7102481e30();

    u8 _8[8];
    UiTexSlots _10;
};

}  // namespace uking::ui
