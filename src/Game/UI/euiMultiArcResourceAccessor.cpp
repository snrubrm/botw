#include "Game/UI/euiMultiArcResourceAccessor.h"
#include <cstdio>
#include <nn/ui2d/Layout.h>
#include <nn/ui2d/Util.h>
#include <new>

namespace eui {

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
