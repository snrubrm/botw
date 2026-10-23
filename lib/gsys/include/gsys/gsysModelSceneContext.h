#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>

namespace agl {
class DrawContext;
class RenderBuffer;
}

namespace sead {
class Viewport;
}

namespace gsys {

class ModelRenderQueue;
class ModelRenderCache;
class RenderBufferContext;
enum class ParticlePass : int;
enum class ParticleShaderType : int;
class ParticleDrawArg;

// One render context of a ModelScene: ModelScene initialize 0x7100c0d9fc allocates the array of 0x3f8-byte
// contexts (sead::Buffer at scene +0x108) and runs the constructor on each.
// TODO: incomplete. Only the members that the particle group functions use are modelled.
class ModelSceneContext {
public:
    // QueueType's enumerators are unrecovered; the accessor only indexes the 0x40-byte array.
    enum QueueType : int;

    ModelSceneContext();
    // 0x7100c21490
    ModelRenderQueue* getRenderQueue(QueueType type) const;
    // 0x7100c21450
    bool isQueueMaskValid(QueueType type, const sead::BitFlag32& mask) const;
    // 0x7100c21514
    bool isDrawParticle(ParticlePass pass) const;
    // 0x7100c2155c (declared only): draws one particle pass into this context. The Graphics
    // particle-editor callbacks (0x7100f2de80 and neighbours) forward to it.
    void drawParticle(agl::DrawContext* draw_context, const RenderBufferContext& render_buffer_context,
                      ParticlePass pass, ParticleShaderType shader_type, u32 mask,
                      ModelRenderCache* cache) const;

    // One per-view record of the 0x3a0-byte view array at +0x18. ModelSceneFx's
    // calcView 0x7100c2f390 and calcViewOccludedEffect 0x7100c2f3c0 read the matrix at +0,
    // the projection at +0xc0, four scalars at +0x140 and a Vector2f at +0x15c.
    struct View {
        sead::Matrix34f mView;
        /* 0x30 */ sead::Matrix34f mInverseView;
        /* 0x60 */ sead::Matrix34f _60;
        u8 _90[0xc0 - 0x90];
        sead::Matrix44f mProjection;
        u8 _100[0x140 - 0x100];
        f32 _140;
        f32 _144;
        f32 _148;
        f32 _14c;
        f32 _150;
        f32 _154;
        f32 _158;
        sead::Vector2f _15c;
        u8 _164[0x3a0 - 0x164];
    };
    static_assert(sizeof(View) == 0x3a0);

    u8 _0[8];
    // The view byte the ModelSceneBuffer switches pass to RenderBufferContext.
    u8 _8;
    u8 _9[0x18 - 9];
    /* 0x18 */ View* mViews;
    u8 _20[0x320 - 0x20];
    // ModelSceneFx::drawOccludedEffect 0x7100c2f40c and drawDebug 0x7100c300d0 pass these to
    // agl::fx::OccludedEffectMgr / VolumeMask.
    /* 0x320 */ const agl::RenderBuffer* mRenderBuffer;
    /* 0x328 */ const sead::Viewport* mViewport;
    u8 _330[0x390 - 0x330];
    // Flag bytes. ModelScene::addParticleGroup sets bit 4 of +0x391 for group 0 and clearParticleGroup clears it.
    u8 _390;
    u8 _391;
    u8 _392;
    // The view index ModelSceneFx::calcViewOccludedEffect 0x7100c2f3c0 scales by 0x3a0.
    /* 0x393 */ u8 mCurrentView;
    u8 _394[0x3a0 - 0x394];
    /* 0x3a0 */ ParticleDrawArg* mParticleDrawArg;
    u8 _3a8[0x3b0 - 0x3a8];
    /* 0x3b0 */ ModelRenderQueue* mRenderQueues;
    u8 _3b8[0x3f8 - 0x3b8];
};
static_assert(sizeof(ModelSceneContext) == 0x3f8);

}  // namespace gsys
