#include "Game/UI/euiMultiArcResourceAccessor.h"
#include <nn/ui2d/Layout.h>
#include <new>

namespace eui {

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
