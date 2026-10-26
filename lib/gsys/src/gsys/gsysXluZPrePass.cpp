#include <gsys/gsysXluZPrePass.h>

namespace gsys {

// 0x7100c67a58
XluZPrePass::XluZPrePass() = default;

// 0x7100c67aa0 (D1) / 0x7100c67af8 (D0)
XluZPrePass::~XluZPrePass() {
    mNodes.freeBuffer();
    mSortNodes.freeBuffer();
}

// 0x7100c67b58
void XluZPrePass::initialize(sead::Heap* heap) {
    mQueues[0].initialize(0x800, heap);
    mQueues[1].initialize(0x800, heap);

    mQueues[0].mSortMode = 0;
    mQueues[1].mSortMode = 1;

    mNodes.allocBuffer(0x800, heap, sizeof(void*));
    mSortNodes.tryAllocBuffer(0x800, heap, sizeof(void*));
}

// 0x7100c67be8
void XluZPrePass::clear() {
    mQueues[0].clear();
    mQueues[1].clear();
}

// 0x7100c67c10
bool XluZPrePass::isValid(const sead::BitFlag32& mask) const {
    const u32 mask_bits = mask;
    if (mQueues[0].mSize >= 1 && (mQueues[0].mRenderMask & mask_bits))
        return true;
    if (mQueues[1].mSize >= 1)
        return (mask_bits | 0x91) & mQueues[1].mRenderMask;
    return false;
}

}  // namespace gsys
