#include <gsys/gsysXluZPrePass.h>

namespace gsys {

// 0x7100c67a58
XluZPrePass::XluZPrePass() = default;

// NON_MATCHING: D1/D0 keep the second queue address in a callee-saved register and move it
// into x0 after the other queue's destructor; ours recomputes it.
// 0x7100c67aa0 (D1) / 0x7100c67af8 (D0)
XluZPrePass::~XluZPrePass() {
    mNodes.freeBuffer();
    mSortNodes.freeBuffer();
}

// 0x7100c67be8
void XluZPrePass::clear() {
    mQueue.clear();
    mSecondQueue.clear();
}

// 0x7100c67c10
bool XluZPrePass::isValid(const sead::BitFlag32& mask) const {
    const u32 mask_bits = mask;
    if (mQueue.mSize >= 1 && (mQueue.mRenderMask & mask_bits))
        return true;
    if (mSecondQueue.mSize >= 1)
        return (mask_bits | 0x91) & mSecondQueue.mRenderMask;
    return false;
}

}  // namespace gsys
