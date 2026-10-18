#pragma once

#include <nn/ui2d/TextureInfo.h>
#include "KingSystem/Resource/resResource.h"

namespace uking::ui {
class Unk_71009cb0c8;
}

namespace agl {
class TextureData;
}

// Native 9CE8C4 / 9CE95C and UiManager's complete lifetime establish this 0x20 pool.
// Three independent resource creators select its texture for the current core.
class Unk_710247ee68 {
public:
    Unk_710247ee68();
    virtual ~Unk_710247ee68();
    agl::TextureData* sub_71009CEA5C();

private:
    agl::TextureData* mTextures[3];
};
KSYS_CHECK_SIZE_NX150(Unk_710247ee68, 0x20);

namespace ksys::res {

// CSV name; vtable 0x710247eae0, constructor 0x71009ccff8.
class ResourceJpg : public Resource {
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

    // Native resource and factory alignment queries both return 0x2000.
    static constexpr size_t cLoadDataAlignment = 0x2000;
    s32 getLoadDataAlignment() const override;
    void sub_71009CD5F8();
    void sub_71009CD66C();
    // Complete decoder 9CD73C and independent load-state consumer 9CB188.
    bool sub_71009CD734(s32 denominator);
    bool sub_71009CDAE0(s32 denominator);

protected:
    // The controller selects the two textures and releases completed decodes in 9CB188 / 9CC970.
    friend class uking::ui::Unk_71009cb0c8;
    bool sub_71009CD73C(s32 denominator, bool secondary);
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
