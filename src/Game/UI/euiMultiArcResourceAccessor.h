#pragma once

#include <nn/ui2d/ResourceAccessor.h>
#include <nn/ui2d/ResourceTextureInfo.h>
#include <nn/ui2d/ArcExtractor.h>
#include <nn/ui2d/ShaderContainer.h>
#include <nn/util/util_IntrusiveList.h>

namespace nn::gfx {
class ResTextureFile;
}

namespace eui {
class ArcResourceMgr;
class FontMgr;

// The original constructor and RTTI prove this ResourceAccessor derivation.
// Only its archive prefix is recovered here; the remaining instance
// layout and virtual interface are not modelled.
class MultiArcResourceAccessor : public nn::ui2d::ResourceAccessor {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::ResourceAccessor)

    MultiArcResourceAccessor(const ArcResourceMgr* arc_resource_mgr, const FontMgr* font_mgr);
    ~MultiArcResourceAccessor() override;

    struct ArchiveLink {
        explicit ArchiveLink(void* data) : extractor(data), textures(nullptr) {}

        nn::util::IntrusiveListNode node;
        nn::ui2d::ArcExtractor extractor;
        nn::gfx::ResTextureFile* textures;
    };

    // A named texture (0x30 bytes, ctor 0x7100be0bb0): list node, an embedded
    // nn::ui2d::ResourceTextureInfo (0x10, vtable 0x24c7f88; not modelled) and a heap copy of the name.
    struct TextureLink {
        nn::util::IntrusiveListNode node;
        nn::ui2d::ResourceTextureInfo texture;
        char* name;
    };
    static_assert(sizeof(TextureLink) == 0x30);

    // 0x7100be022c: archive animation lookup; writes the byte size when requested.
    const void* sub_7100BE022C(const char* layout_name, const char* animation_name, u32* size);

    // Declared only (0x7100be06b4 / 0x7100be0738 / 0x7100be07c0 / 0x7100be03f4 / 0x7100be050c / 0x7100be0540).
    void RegisterTextureViewToDescriptorPool(TextureViewDescriptorCallback callback,
                                             void* user_data) override;
    void UnregisterTextureViewFromDescriptorPool(TextureViewDescriptorCallback callback,
                                                 void* user_data) override;
    void Finalize(nn::gfx::Device* device) override;
    void* GetResource(size_t* size, u32 type, const char* name) override;
    nn::font::Font* AcquireFont(nn::gfx::Device* device, const char* name) override;
    nn::ui2d::TextureInfo* AcquireTexture(nn::gfx::Device* device, const char* name) override;

    bool isArchiveAttached(void* data);
    void attachArchive(void* data, nn::gfx::ResTextureFile* textures);
    bool LoadTexture(nn::ui2d::ResourceTextureInfo* texture, nn::gfx::Device* device,
                     const char* name) override;
    nn::ui2d::ShaderInfo* AcquireShader(nn::gfx::Device* device, const char* name) override;
    bool LoadShader(nn::ui2d::ShaderInfo* shader, nn::gfx::Device* device,
                    const char* name) override;

    /* 0x08 */ const ArcResourceMgr* mArcResourceMgr;
    /* 0x10 */ const FontMgr* mFontMgr;
    /* 0x18 */ nn::ui2d::ShaderContainer mShaders;
    using ArchiveList = nn::util::IntrusiveList<
        ArchiveLink, nn::util::IntrusiveListMemberNodeTraits<ArchiveLink, &ArchiveLink::node>>;
    /* 0x28 */ ArchiveList mArchives;
    using TextureList = nn::util::IntrusiveList<
        TextureLink, nn::util::IntrusiveListMemberNodeTraits<TextureLink, &TextureLink::node>>;
    /* 0x38 */ TextureList mTextures;
};
static_assert(sizeof(MultiArcResourceAccessor) == 0x48);

}  // namespace eui
