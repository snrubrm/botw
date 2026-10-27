#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>
#include <container/seadTList.h>
#include <environment/aglEnvObjMgr.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <hostio/seadHostIONode.h>
#include <lighting/aglLightMapMgr.h>
#include <utility/aglDebugTexturePage.h>

namespace gsys {

class ModelRenderQueue;

// Partial: only the draw gate is known; the texture's own vtable and render targets are not
// modelled.
class SnapshotTexture {
public:
    // 0x7100c84618: always true in this build.
    bool checkEnableToDraw();
};

class SnapshotTextureMgr : public sead::hostio::Node {
public:
    // A snapshot render target: its own vtable plus a colour target, the colour
    // buffer and the sampler it renders through.
    class ExpansionColor {
    public:
        // 0x7100c60258 / 0x7100c602b0
        virtual ~ExpansionColor();

    private:
        /* 0x08 */ agl::RenderTargetColor mRenderTargetColor;
        /* 0x180 */ agl::RenderBuffer mRenderBuffer;
        /* 0x1e8 */ agl::TextureSampler mSampler;
    };

    // 0x7100c60824
    SnapshotTextureMgr();

    // 0x7100c60dac
    void setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1);
    // 0x7100c60c94
    void updateGPU();

private:
    /* 0x08 */ sead::TList<SnapshotTexture*> mTextures;
    /* 0x20 */ sead::TList<SnapshotTexture*> mUnk20;
    /* 0x38 */ sead::TList<SnapshotTexture*> mUnk38;
    /* 0x50 */ ModelRenderQueue* mRenderQueues[2];
    /* 0x60 */ SnapshotTexture* mCurrentTexture = nullptr;
    /* 0x68 */ sead::DirectCamera mCamera;
    /* 0xd0 */ sead::DirectProjection mProjection;
    /* 0x1c8 */ agl::RenderTargetColor mColorTarget0;
    /* 0x340 */ agl::RenderTargetDepth mDepthTarget;
    /* 0x4b8 */ agl::RenderBuffer mBuffer0;
    /* 0x520 */ agl::RenderTargetColor mColorTarget1;
    /* 0x698 */ agl::RenderBuffer mBuffer1;
    /* 0x700 */ agl::utl::DebugTexturePage mDebugTexturePage;
    // Set once the light maps have been updated, cleared when the GPU upload is done.
    /* 0x940 */ bool mLightMapUpdated;
    /* 0x941 */ u8 _941[0x948 - 0x941];
    /* 0x948 */ agl::env::EnvObjMgr mEnvObjMgr;
    // EnvObjMgr's modelled prefix is 0x288 bytes; the original extent is 0x490.
    /* 0xbd0 */ u8 _bd0[0xdd8 - 0xbd0];
    /* 0xdd8 */ agl::lght::LightMapMgr mLightMapMgr;
    /* 0x3de0 */ ExpansionColor mExpansionColor;
};

static_assert(sizeof(SnapshotTextureMgr) == 0x4138);

}  // namespace gsys
