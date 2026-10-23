#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelRenderContext.h>
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
//
// ModelSceneContext derives from ModelRenderContext at +0 (constructor 0x7100c20ec4 calls
// ModelRenderContext::ModelRenderContext with `this`, D1 0x7100c20f3c tail-calls its D1, and drawCloud
// 0x7100c2fb7c passes the context straight to ModelRenderContext::bind). The 0x388-byte base holds the
// view records (+0x10 count, +0x18 array), the view byte at +0x8 and the render buffer / viewport at
// +0x320 / +0x328, all of which the effect component reads through this type.
//
// The remaining 0x70 bytes are a second polymorphic base: the constructor and D1 store a second vptr at
// +0x388 (the vtable group's secondary table, offset-to-top -0x388, one slot, hostio::Node's type getter)
// and initializeScene 0x7100c21004 passes this + 0x388 to gsys::ORUtil::setNodeMetaIcon as a
// sead::hostio::Node*. The class itself has no members. It is not modelled yet, so its vptr slot is padding.
// TODO: incomplete. Only the members that the particle group functions use are modelled.
class ModelSceneContext : public ModelRenderContext {
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

    // Padding for the unmodelled second base's vptr at +0x388.
    u8 _388[8];
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
