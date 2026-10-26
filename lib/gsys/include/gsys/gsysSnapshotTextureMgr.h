#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>
#include <gfx/seadCamera.h>
#include <lighting/aglLightMapMgr.h>

namespace gsys {

class ModelRenderQueue;

// TODO: incomplete. The render-queue slots, camera and light-map manager that the
// modelled members use are declared; the rest of the snapshot texture manager is not.
class SnapshotTextureMgr {
public:
    // A snapshot render target: its own vtable plus a colour target, the colour
    // buffer, its sampler and the texture it renders into.
    class ExpansionColor {
    public:
        // 0x7100c60258 / 0x7100c602b0
        virtual ~ExpansionColor();

    private:
        /* 0x08 */ agl::RenderTargetColor mRenderTargetColor;
        /* 0x180 */ agl::RenderBuffer mRenderBuffer;
        /* 0x1e8 */ agl::TextureSampler mSampler;
    };

    // 0x7100c60dac
    void setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1);
    // 0x7100c60c94
    void updateGPU();

private:
    u8 _0[0x50];
    /* 0x50 */ ModelRenderQueue* mRenderQueues[2];
    /* 0x60 */ u8 _60[0x8];
    /* 0x68 */ sead::DirectCamera mCamera;
    /* 0xd0 */ u8 _d0[0x940 - 0xd0];
    // Set once the light maps have been updated, cleared when the GPU upload is done.
    /* 0x940 */ bool mLightMapUpdated;
    /* 0x941 */ u8 _941[0xdd8 - 0x941];
    /* 0xdd8 */ agl::lght::LightMapMgr mLightMapMgr;
};

}  // namespace gsys
