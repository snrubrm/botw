#pragma once

#include <common/aglGPUMemAddr.h>
#include <common/aglTextureData.h>
#include <common/aglTextureSampler.h>
#include <nn/gfx/gfx_ResTextureData.h>
#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::tera {

// vtable 0x710251ce88 (D1 / D0 only); constructor 0x71012df5b4. A square R8_G8_B8_A8 texture in its
// own GPU memory with a sampler and a ResTextureData view (its users 0x710106ad3c .. are not
// decompiled yet).
class Unk_710251ce88 {
public:
    Unk_710251ce88();
    virtual ~Unk_710251ce88();

    // 0x71012df734 (placeholder name): creates the size x size texture and its memory, clears it and
    // sets up the ResTextureData and the sampler.
    void init(u32 size, sead::Heap* heap);
    // 0x71012df674 (placeholder name): frees the texture data and the GPU memory.
    void finalize();
    // 0x71012df984 (placeholder name): flushes the CPU cache of the image.
    void flush();

private:
    u32 mSize = 0;
    u32 mByteSize = 0;
    u32 mBytesPerPixel = 0;
    u32 mRowPixels = 0;
    agl::GPUMemAddrBase mAddress;
    agl::TextureData* mTextureData = nullptr;
    agl::TextureSampler mSampler;
    nn::gfx::ResTextureData mResTexture;
    u8 _248[0x254 - 0x248];
    f32 _254 = 1.0f;
};

}  // namespace ksys::tera
