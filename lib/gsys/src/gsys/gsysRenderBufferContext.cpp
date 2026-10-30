#include <gsys/gsysRenderBufferContext.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace gsys {

RenderBufferContext::Context::Context() = default;
// NON_MATCHING: the compiler schedules member addresses using different saved registers.
RenderBufferContext::Context::~Context() = default;

// 0x7100c5ccb8
RenderBufferContext::BufferData::BufferData() {
    mRenderBuffer.setRenderTargetColor(&mColorTarget0, 0);
    mRenderBuffer.setRenderTargetDepth(&mDepthTarget);
    mSampler0.setFilter(1, 1, 0);
    mSampler1.setFilter(0, 0, 0);
    mSampler3.setFilter(0, 0, 0);
}


// 0x7100c5b800
// NON_MATCHING: RenderTargetDepth::setStorage (GPUMemAddrBase::operator=) stores the 4-byte
// offset with its padding as one 8-byte store here; the target stores 4 bytes. Same residue as
// GBuffer::endDeferredShading.
void RenderBufferContext::BufferData::enableHiZ(bool enable) {
    mDepthTarget.setStorage(enable ? mHiZAddr : agl::GPUMemVoidAddr());
}

// 0x7100c5cdb4
// NON_MATCHING: same call sequence and order; the target keeps two sampler bases in
// callee-saved registers, this build recomputes them (scheduling only).
RenderBufferContext::BufferData::~BufferData() {    if (mTexture0) {
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture0);
        mTexture0 = nullptr;
    }
    if (mHiZTexture) {
        agl::utl::DynamicTextureAllocator::instance()->free(mHiZTexture);
        mHiZTexture = nullptr;
        mHiZAddr.invalidate();
    }
    if (mTexture2) {
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture2);
        mTexture2 = nullptr;
    }
}

}  // namespace gsys
