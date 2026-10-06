#include "Game/UI/euiMultiArcResourceAccessor.h"
#include <prim/seadStringBuilder.h>
#include "Game/UI/euiFontMgr.h"
#include <cstdio>
#include <nn/gfx/gfx_ResTexture.h>
#include <nn/ui2d/Layout.h>
#include <nn/ui2d/Util.h>
#include <new>

namespace eui {

MultiArcResourceAccessor::MultiArcResourceAccessor(const ArcResourceMgr* arc_resource_mgr,
                                                   const FontMgr* font_mgr)
    : mArcResourceMgr(arc_resource_mgr), mFontMgr(font_mgr) {}

MultiArcResourceAccessor::~MultiArcResourceAccessor() {
    for (auto it = mTextures.begin(); it != mTextures.end();) {
        TextureLink& texture = *it;
        ++it;
        nn::ui2d::Layout::FreeMemory(texture.name);
        nn::ui2d::Layout::FreeMemory(&texture);
    }
    for (auto it = mArchives.begin(); it != mArchives.end();) {
        ArchiveLink& archive = *it;
        ++it;
        archive.~ArchiveLink();
        nn::ui2d::Layout::FreeMemory(&archive);
    }
}

// NON_MATCHING: matches once nn::util::IntrusiveList::size() is defined inline in lib (the
// original counts the nodes inline); until then it is an undefined call.
// 0x7100be022c
const void* MultiArcResourceAccessor::sub_7100BE022C(const char* layout_name,
                                                     const char* animation_name, u32* size) {
    sead::FixedStringBuilder<256> path;
    nn::ui2d::ArcExtractor* extractor;
    if (mArchives.size() == 1) {
        extractor = &mArchives.begin()->extractor;
    } else {
        path.copy("blyt/", 5);
        path.append(layout_name, -1);
        path.append(".bflyt", 6);
        for (auto it = mArchives.begin();; ++it) {
            if (!(it != mArchives.end()))
                return nullptr;
            nn::ui2d::ArcFileInfo info{};
            extractor = &it->extractor;
            const s32 entry_id = extractor->ConvertPathToEntryId(path.cstr());
            if (entry_id >= 0 && extractor->GetFileFast(&info, entry_id))
                break;
        }
    }

    path.copy("anim/", 5);
    path.append(layout_name, -1);
    path.append("_", 1);
    path.append(animation_name, -1);
    path.append(".bflan", 6);
    nn::ui2d::ArcFileInfo info{};
    const s32 entry_id = extractor->ConvertPathToEntryId(path.cstr());
    if (entry_id < 0)
        return nullptr;
    const void* data = extractor->GetFileFast(&info, entry_id);
    if (data) {
        if (size)
            *size = info.size;
        return data;
    }
    return nullptr;
}

// NON_MATCHING: the original sign-extends the file size (ldursw): needs nn::ui2d::ArcFileInfo::size
// to be s32 (lib); with u32 only that load differs.
// 0x7100be03f4
void* MultiArcResourceAccessor::GetResource(size_t* size, u32 type, const char* name) {
    sead::FixedStringBuilder<256> path;
    {
        const char type_name[5] = {char(type >> 24), char(type >> 16), char(type >> 8), char(type),
                                   0};
        path.copy(type_name, 4);
    }
    path.append("/", 1);
    path.append(name, -1);
    for (auto& link : mArchives) {
        nn::ui2d::ArcFileInfo info{};
        const s32 entry_id = link.extractor.ConvertPathToEntryId(path.cstr());
        if (entry_id < 0)
            continue;
        if (void* data = const_cast<void*>(link.extractor.GetFileFast(&info, entry_id))) {
            if (size)
                *size = info.size;
            return data;
        }
    }
    return nullptr;
}

// 0x7100be050c
nn::font::Font* MultiArcResourceAccessor::AcquireFont(nn::gfx::Device*, const char* name) {
    return mFontMgr->tryGetFont(name);
}

bool MultiArcResourceAccessor::LoadTexture(nn::ui2d::ResourceTextureInfo* texture,
                                         nn::gfx::Device* device, const char* name) {
    for (auto& archive : mArchives) {
        if (!archive.textures)
            continue;
        auto& container = archive.textures->ToData().textureContainerData;
        const int index = container.pTextureDic.Get()->FindIndex(nn::util::string_view(name));
        if (index != nn::util::ResDic::Npos)
            return nn::ui2d::LoadTexture(texture, device,
                                       container.pTexturePtrArray.Get()[index].Get());
    }
    return false;
}

nn::ui2d::ShaderInfo* MultiArcResourceAccessor::AcquireShader(nn::gfx::Device* device,
                                                           const char* name) {
    auto* shader = mShaders.FindShaderByName(name);
    if (!shader) {
        shader = mShaders.RegisterShader(name, false);
        if (shader)
            LoadShader(shader, device, name);
    }
    return shader;
}

bool MultiArcResourceAccessor::LoadShader(nn::ui2d::ShaderInfo* shader, nn::gfx::Device* device,
                                        const char* name) {
    s32 source_blend;
    s32 destination_blend;
    if (nn::ui2d::ConvertArchiveShaderNameToBlends(&source_blend, &destination_blend, name)) {
        for (auto& archive : mArchives) {
            nn::ui2d::ArcFileInfo info{};
            const s32 shader_id = archive.extractor.ConvertPathToEntryId("bgsh/__ArchiveShader.bnsh");
            if (shader_id < 0)
                continue;
            const void* shader_data = archive.extractor.GetFileFast(&info, shader_id);
            if (!shader_data || info.size == 0)
                continue;
            const s32 table_id = archive.extractor.ConvertPathToEntryId("bgsh/__ArchiveShader.bushvt");
            if (table_id < 0)
                continue;
            const void* table = archive.extractor.GetFileFast(&info, table_id);
            if (!table || info.size == 0)
                continue;
            if (nn::ui2d::SearchShaderVariationIndexFromTable(table, source_blend,
                                                           destination_blend) == -1)
                continue;
            nn::ui2d::LoadArchiveShader(shader, device, const_cast<void*>(shader_data), table,
                                       nullptr, 0, 0);
            return true;
        }
        return false;
    }

    char filename[256];
    std::snprintf(filename, sizeof(filename), "ArchiveShader-%s.bnsh", name);
    size_t size = 0;
    void* data = GetResource(&size, 0x62677368, filename);
    if (!data && size == 0)
        return false;
    nn::ui2d::LoadArchiveShader(shader, device, data, nullptr, nullptr, 0, 0);
    return true;
}

bool MultiArcResourceAccessor::isArchiveAttached(void* data) {
    for (auto& archive : mArchives) {
        if (archive.extractor.mArchive == data)
            return true;
    }
    return false;
}

// NON_MATCHING: the compiler removes the allocation guard and the overwritten texture reset.
void MultiArcResourceAccessor::attachArchive(void* data, nn::gfx::ResTextureFile* textures) {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(ArchiveLink), 4);
    auto* archive = memory ? new (memory) ArchiveLink(data) : nullptr;
    archive->textures = textures;
    mArchives.push_front(*archive);
}

}  // namespace eui
