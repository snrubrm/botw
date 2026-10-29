#pragma once

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>

namespace agl {
class DrawContext;
class TextureData;
}  // namespace agl

namespace sead {
class Heap;
}

namespace gsys {

// The outline renderer's silhouette depth buffers (vtable 0x71024cee80).
class Outline : public sead::hostio::Node {
public:
    // The mode stored at +0x18; initialize allocates the depth buffers only for mode 1.
    enum eMode {
        cMode_0,
        cMode_1,
    };

    // One silhouette depth target. initialize 0x7100c4e094 allocates 0x360 bytes per buffer.
    class SilhouetteDepthBuffer {
    public:
        SilhouetteDepthBuffer() { setSize(1280, 720); }

        // 0x7100c4e214 (declared only).
        void begin(agl::DrawContext* context);

        // inline-only in the original; name is a guess. The constructor and
        // setSilhouetteDeptBufferSize 0x7100c4e18c both store the size and the render buffer's
        // virtual size and physical area.
        void setSize(s32 width, s32 height) {
            mWidth = width;
            mHeight = height;
            const f32 w = width;
            const f32 h = height;
            mRenderBuffer.setPhysicalArea(sead::BoundBox2f(0.0f, 0.0f, w, h));
            mRenderBuffer.setVirtualSize(sead::Vector2f(w, h));
        }

        const agl::TextureData* mTexture = nullptr;
        agl::RenderTargetDepth mDepthTarget;  // +0x8
        agl::RenderBuffer mRenderBuffer;      // +0x180
        agl::TextureSampler mSampler;         // +0x1e8
        s32 mWidth;                           // +0x358
        s32 mHeight;                          // +0x35c
    };

    Outline();
    virtual ~Outline();

    void initialize(int num, sead::Heap* heap, eMode mode);
    void setSilhouetteDeptBufferSize(int width, int height, int index);
    void beginSilhouetteDepthBuffer(agl::DrawContext* context, int index);
    void invalidateSilhouetteDepthBuffer(agl::DrawContext* context, int index);
    void endSilhouetteDepthBuffer(int index);
    const agl::TextureSampler& getSilhouetteDepthBufferSampler(int index) const;

private:
    sead::PtrArray<SilhouetteDepthBuffer> mBuffers;  // +0x8
    eMode mMode;                                     // +0x18
};

}  // namespace gsys
