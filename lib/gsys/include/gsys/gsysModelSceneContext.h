#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadViewport.h>
#include <gsys/gsysModelRenderContext.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>

namespace agl {
class DrawContext;
class RenderBuffer;
}

namespace gsys {

class Layer3D;
class ModelRenderQueue;
class ModelRenderCache;
class RenderBufferContext;
enum class ParticlePass : int;
enum class ParticleShaderType : int;
class ParticleDrawArg;

// One render context of a ModelScene: ModelScene initialize 0x7100c0d9fc allocates the array of 0x3f8-byte
// contexts (sead::Buffer at scene +0x108) and runs the constructor on each.
//
// ModelSceneContext derives from ModelRenderContext at +0 (constructor 0x7100c20ec4 calls
// ModelRenderContext::ModelRenderContext with `this`, D1 0x7100c20f3c tail-calls its D1, and drawCloud
// 0x7100c2fb7c passes the context straight to ModelRenderContext::bind). The 0x388-byte base holds the
// view records (+0x10 count, +0x18 array), the view byte at +0x8 and the render buffer / viewport at
// +0x320 / +0x328, all of which the effect component reads through this type.
//
// The remaining 0x70 bytes start with a sead::hostio::Node base at +0x388. The constructor 0x7100c20ec4
// stores the secondary table of ModelSceneContext's group there once and ends with the Viewport
// constructor, so the Node subobject is just its vptr: the fields from +0x390 on are ModelSceneContext's
// own members. initializeScene 0x7100c21004 passes this + 0x388 to gsys::ORUtil::setNodeMetaIcon as a
// sead::hostio::Node*.
// TODO: incomplete. Only the members that the particle group functions use are modelled.
class ModelSceneContext : public ModelRenderContext, public sead::hostio::Node {
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

    // The fields after the Node subobject. The constructor 0x7100c20ec4 inlines their initial values.
    /* 0x390 */ u8 mFlags = 0x30;
    /* 0x391 */ u8 mParticleFlags = 0x01;
    // Set to 0xff by calc 0x7100c21368.
    /* 0x392 */ u8 _392;
    /* 0x393 */ u8 mCurrentView = 0;
    /* 0x394 */ u8 _394[0x398 - 0x394];
    /* 0x398 */ Layer3D* _398 = nullptr;
    /* 0x3a0 */ ParticleDrawArg* mParticleDrawArg = nullptr;
    /* 0x3a8 */ void* _3a8 = nullptr;
    // Cleared by initializeScene 0x7100c21004 and calc; not set by the constructor.
    /* 0x3b0 */ ModelRenderQueue* mRenderQueues;
    /* 0x3b8 */ f32 _3b8 = 1000.0f;
    /* 0x3bc */ f32 _3bc = -1000.0f;
    /* 0x3c0 */ f32 _3c0 = -1000.0f;
    /* 0x3c4 */ f32 _3c4 = 0.2f;
    /* 0x3c8 */ f32 _3c8 = 0;
    /* 0x3cc */ u8 _3cc[4];
    /* 0x3d0 */ sead::Viewport mViewport;
};
static_assert(sizeof(ModelSceneContext) == 0x3f8);

}  // namespace gsys
