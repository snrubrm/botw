#pragma once

#include <nn/ui2d/ResourceAccessor.h>
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

    ~MultiArcResourceAccessor() override;

    struct ArchiveLink {
        explicit ArchiveLink(void* data) : extractor(data), textures(nullptr) {}

        nn::util::IntrusiveListNode node;
        nn::ui2d::ArcExtractor extractor;
        nn::gfx::ResTextureFile* textures;
    };

    // 0x7100be022c: archive animation lookup; writes the byte size when requested.
    const void* sub_7100BE022C(const char* layout_name, const char* animation_name, u32* size);

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
};

}  // namespace eui
