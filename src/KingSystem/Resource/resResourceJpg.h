#pragma once

#include <nn/ui2d/TextureInfo.h>
#include "KingSystem/Resource/resResource.h"

namespace agl {
class TextureData;
}

namespace ksys::res {

// CSV name; vtable 0x710247eae0, constructor 0x71009ccff8.
class ResourceJpg : public Resource {
    // NON_MATCHING: the inherited Resource RTTI check is inlined rather than the original tail call.
    SEAD_RTTI_OVERRIDE(ResourceJpg, Resource)
public:
    ResourceJpg();
    ~ResourceJpg() override;

    static constexpr size_t cLoadDataAlignment = 0x2000;
    s32 getLoadDataAlignment() const override;
    bool m2_() override;

protected:
    void doCreate_(u8* data, u32 size, sead::Heap* heap) override;
    void onDestroy_() override;
    virtual u32 sub_71009CD408();

    nn::ui2d::ExternalTextureInfo _38;
    bool _50 = false;
    nn::ui2d::ExternalTextureInfo _58;
    agl::TextureData* _70 = nullptr;
    agl::TextureData* _78 = nullptr;
};
KSYS_CHECK_SIZE_NX150(ResourceJpg, 0x80);

// Constructor 0x71009CD4B0 and factory 0x7100A80AF0 prove this separate 0x80 resource.
// Its two ExternalTextureInfo objects are consumed by 0x71009CD73C and 0x71009CB188.
class Unk_710247eb88 : public Resource {
    SEAD_RTTI_OVERRIDE(Unk_710247eb88, Resource)
public:
    Unk_710247eb88();
    ~Unk_710247eb88() override;

    s32 getLoadDataAlignment() const override;
    void sub_71009CD5F8();
    void sub_71009CD66C();

protected:
    void sub_71009CDAE8();

    bool _38 = false;
    bool _39 = false;
    nn::ui2d::ExternalTextureInfo _40;
    nn::ui2d::ExternalTextureInfo _58;
    agl::TextureData* _70 = nullptr;
    agl::TextureData* _78 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710247eb88, 0x80);

}  // namespace ksys::res
