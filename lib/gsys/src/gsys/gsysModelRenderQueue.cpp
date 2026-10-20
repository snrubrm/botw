#include <gsys/gsysModelRenderQueue.h>

#include <heap/seadHeap.h>

namespace gsys {

ModelRenderQueue::ModelRenderQueue() = default;

ModelRenderQueue::~ModelRenderQueue() {
    // Release the raw pointer storage through the native scalar deallocator.
    if (mNodes)
        ::operator delete(mNodes);
}

void ModelRenderQueue::initialize(int capacity, sead::Heap* heap) {
    const int aligned_capacity = (capacity + 7) & ~7;
    mNodes = new (heap, 0x40) ModelRenderUnitSortNode*[aligned_capacity];
    mSortNodes = mNodes;
    mCapacity = aligned_capacity;
    mSize = 0;
}

void ModelRenderQueue::clear() {
    mSize = 0;
    mRenderMask = 0;
    mPassTextureMask = 0;
}

// 0x7100c09948 is the Job entry point, a tail call to the queue's sort operation.
void ModelRenderQueue::invoke() {
    sort();
}

}  // namespace gsys
