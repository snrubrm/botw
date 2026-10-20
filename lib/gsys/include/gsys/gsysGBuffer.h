#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace agl {
class DrawContext;
}

namespace gsys {

// RenderBufferContext::initialize C5934C allocates 0x3378 bytes and calls C70958.
// The constructor installs the destructor-only vtable 24D0DA8; remaining state is opaque.
class GBuffer {
public:
    enum class Resolution : int;

    GBuffer();
    virtual ~GBuffer();
    void initialize(sead::Heap* heap);
    void invalidateGPUWriteCache(agl::DrawContext*, const sead::SafeString&, Resolution) const;

private:
    u8 _8[0x3378 - 8];
};
static_assert(sizeof(GBuffer) == 0x3378);

}  // namespace gsys
