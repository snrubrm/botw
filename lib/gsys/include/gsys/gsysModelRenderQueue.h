#pragma once

#include <basis/seadTypes.h>
#include <mc/seadJob.h>
#include <thread/seadAtomic.h>

namespace gsys {

class ModelRenderUnitSortNode;

// Constructor 0x7100c09008 installs the Job-derived vtable and initializes the
// name, sort mode and masks. initialize owns the node-pointer array at +0x28;
// sort reads the selected array at +0x30 and its count at +0x3c.
class ModelRenderQueue : public sead::Job {
public:
    ModelRenderQueue();
    ~ModelRenderQueue() override;
    void invoke() override;

    void initialize(int capacity, sead::Heap* heap);
    void clear();
    void sort();

private:
    s32 mSortMode = 0;
    u32 mRenderMask = 0;
    u32 mPassTextureMask = 0;
    ModelRenderUnitSortNode** mNodes = nullptr;
    ModelRenderUnitSortNode** mSortNodes;
    s32 mCapacity;
    // pushBackQueue_<false,false> 0x7100c4378c increments +0x3c with
    // an exclusive load/store before writing the selected node pointer.
    sead::Atomic<s32> mSize = 0;
};
static_assert(sizeof(ModelRenderQueue) == 0x40);

}  // namespace gsys
