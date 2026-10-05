#include "Game/UI/euiMultiArcResourceAccessor.h"
#include <nn/ui2d/Layout.h>
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
