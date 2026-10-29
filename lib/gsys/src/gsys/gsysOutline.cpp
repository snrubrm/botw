#include "gsys/gsysOutline.h"
#include <common/aglTextureData.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace gsys {

// 0x7100c4dfb0
Outline::Outline() = default;

// 0x7100c4dfc8
Outline::~Outline() {
    for (s32 i = 0; i < mBuffers.size(); ++i)
        delete mBuffers[i];
    mBuffers.freeBuffer();
}

// 0x7100c4e094
void Outline::initialize(int num, sead::Heap* heap, eMode mode) {
    mMode = mode;
    if (mode != cMode_1)
        return;

    mBuffers.allocBuffer(num, heap);
    for (s32 i = 0; i < num; ++i)
        mBuffers.pushBack(new (heap) SilhouetteDepthBuffer);
}

// 0x7100c4e18c
void Outline::setSilhouetteDeptBufferSize(int width, int height, int index) {
    mBuffers[index]->setSize(width, height);
}

// 0x7100c4e1f4
void Outline::beginSilhouetteDepthBuffer(agl::DrawContext* context, int index) {
    mBuffers[index]->begin(context);
}

// 0x7100c4e3a0. Only the image address lookup survives in the original (its result is
// discarded); the draw context is unused.
void Outline::invalidateSilhouetteDepthBuffer(agl::DrawContext* context, int index) {
    mBuffers(index)->mTexture->getImagePtr().getAddress();
}

// 0x7100c4e3c8
// NON_MATCHING: the allocator and buffer pointer loads are ordered differently.
void Outline::endSilhouetteDepthBuffer(int index) {
    agl::utl::DynamicTextureAllocator::instance()->free(mBuffers(index)->mTexture);
}

// 0x7100c4e3e4
const agl::TextureSampler& Outline::getSilhouetteDepthBufferSampler(int index) const {
    return mBuffers[index]->mSampler;
}

}  // namespace gsys
