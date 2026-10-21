#pragma once

#include <basis/seadTypes.h>

namespace gsys {

class ModelRenderQueue;
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

    u8 _0[8];
    // The view byte the ModelSceneBuffer switches pass to RenderBufferContext.
    u8 _8;
    u8 _9[0x390 - 9];
    // Flag bytes. ModelScene::addParticleGroup sets bit 4 of +0x391 for group 0 and clearParticleGroup clears it.
    u8 _390;
    u8 _391;
    u8 _392[0x3a0 - 0x392];
    /* 0x3a0 */ ParticleDrawArg* mParticleDrawArg;
    u8 _3a8[0x3b0 - 0x3a8];
    /* 0x3b0 */ ModelRenderQueue* mRenderQueues;
    u8 _3b8[0x3f8 - 0x3b8];
};
static_assert(sizeof(ModelSceneContext) == 0x3f8);

}  // namespace gsys
