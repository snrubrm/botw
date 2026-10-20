#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

namespace gsys {

class ModelRenderUnit;

// 0x7100c0994c clears the entire 0x18-byte node. ModelUnit::pushBackQueue_
// 0x7100c4378c writes the render unit, mask, index, packed draw flags, material,
// sort key and depth at these offsets before publishing its pointer to a queue.
class ModelRenderUnitSortNode {
public:
    ModelRenderUnitSortNode();

    ModelRenderUnit* mRenderUnit = nullptr;
    u32 mRenderMask = 0;
    u8 mIndex = 0;
    u8 mDrawFlags = 0;
    u16 mMaterialIndex = 0;
    u32 mSortKey = 0;
    f32 mDepth = 0;
};
static_assert(sizeof(ModelRenderUnitSortNode) == 0x18);

// initialize 0x7100c099f0 allocates the 0x18-byte node array with alignment 0x20.
// Its destructor frees the Buffer at +0x08; the vtable has just D1 and D0.
class ModelRenderUnitNodeArray {
public:
    ModelRenderUnitNodeArray();
    virtual ~ModelRenderUnitNodeArray();

    bool initialize(int count, sead::Heap* heap);

private:
    sead::Buffer<ModelRenderUnitSortNode> mNodes;
};
static_assert(sizeof(ModelRenderUnitNodeArray) == 0x18);

}  // namespace gsys
