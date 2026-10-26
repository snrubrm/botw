#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <prim/seadBitFlag.h>
#include "gsys/gsysModelRenderQueue.h"

namespace agl {
class DrawContext;
}

namespace sead {
class Heap;
}

namespace gsys {

class ModelRenderUnitSortNode;
class ModelSceneContext;

/// The extra translucent pre-pass. Layout from the constructor 0x7100c67a58 and the destructor
/// 0x7100c67aa0: two render queues (an array; the destructor walks it), a pointer array of nodes
/// and their sort buffer.
class XluZPrePass {
public:
    XluZPrePass();
    virtual ~XluZPrePass();

    // 0x7100c67b58 (declared only; body U).
    void initialize(sead::Heap* heap);
    void clear();
    bool isValid(const sead::BitFlag32& mask) const;
    // 0x7100c67c60 / 0x7100c68018 (declared only; bodies U).
    void sort();
    void draw(agl::DrawContext* context, const ModelSceneContext& scene_context,
              const sead::BitFlag32& mask, bool a) const;

private:
    /* 0x08 */ ModelRenderQueue mQueues[2];
    /* 0x88 */ sead::PtrArray<ModelRenderUnitSortNode> mNodes;
    /* 0x98 */ sead::Buffer<ModelRenderUnitSortNode*> mSortNodes;
};
static_assert(sizeof(XluZPrePass) == 0xa8);

}  // namespace gsys
