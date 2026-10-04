#pragma once

#include <nn/ui2d/ResourceAccessor.h>

namespace eui {
class ArcResourceMgr;

// The original constructor and RTTI prove this ResourceAccessor derivation.
// Only its archive-manager pointer is recovered here; the remaining instance
// layout and virtual interface are not modelled.
class MultiArcResourceAccessor : public nn::ui2d::ResourceAccessor {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::ResourceAccessor)

    // 0x7100be022c: archive animation lookup; writes the byte size when requested.
    const void* sub_7100BE022C(const char* layout_name, const char* animation_name, u32* size);

    bool isArchiveAttached(void* data);
    void attachArchive(void* data, nn::gfx::ResTextureFile* textures);

    /* 0x08 */ const ArcResourceMgr* mArcResourceMgr;
};

}  // namespace eui
