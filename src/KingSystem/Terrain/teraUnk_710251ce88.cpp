#include "KingSystem/Terrain/teraUnk_710251ce88.h"
#include <common/aglGPUMemBlock.h>
#include <cstring>
#include <g3d/aglTextureUtilG3D.h>

namespace ksys::tera {

Unk_710251ce88::Unk_710251ce88() {
    std::memset(&mResTexture, 0, sizeof(mResTexture));
}

Unk_710251ce88::~Unk_710251ce88() {
    finalize();
}

void Unk_710251ce88::finalize() {
    if (mTextureData) {
        delete mTextureData;
        mTextureData = nullptr;
    }
    if (mAddress.isValid())
        mAddress.deleteGPUMemBlock();
    mSize = 0;
    mByteSize = 0;
    mBytesPerPixel = 0;
    mRowPixels = 0;
}

// NON_MATCHING: the original loads the texture data pointer together with the address block (ldp) when
// it copies the address for setImagePtr (scheduling).
void Unk_710251ce88::init(u32 size, sead::Heap* heap) {
    mSize = size;
    mTextureData = new (heap, 8) agl::TextureData;
    mTextureData->initialize_(agl::TextureType::cTextureType_2D,
                              agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, mSize, mSize, 1,
                              1, agl::TextureAttribute(1), agl::MultiSampleType{}, true);
    const u32 byte_size = mTextureData->getImageByteSize();
    mByteSize = byte_size;
    mBytesPerPixel = 4;
    mRowPixels = byte_size / (mSize * 4);
    const u32 alignment = mTextureData->getImageAlignment();
    auto* memory = new (heap, 8) agl::GPUMemBlock<u8>;
    memory->allocBuffer_(byte_size, heap, alignment, agl::MemoryAttribute::CpuCached);
    mAddress = agl::GPUMemAddrBase(*memory, 0);
    if (!mAddress.isValid())
        return;
    mTextureData->setImagePtr(mAddress, 0);
    std::memset(mAddress.getAddress(), 0, mByteSize);
    mAddress.flushCPUCache(mByteSize);
    agl::g3d::TextureUtilG3D::convertToResTexture(&mResTexture, *mTextureData, nullptr);
    mSampler.applyTextureData(*mTextureData);
    mSampler.setWrap(1, 1, 1);
    mSampler.setFilter(1, 1, 1);
}

void Unk_710251ce88::flush() {
    if (mAddress.isValid())
        mAddress.flushCPUCache(mByteSize);
}

}  // namespace ksys::tera
