#include "aal/aalSpatialCalculator.h"

namespace aal {

// 0x7100b8fb00
s32 SpatialCalculator::getResultNum() const {
    if (mResults.getBufferPtr())
        return mResults.size();
    return 0;
}

// 0x7100b8fab8
const SpatialCalculator::Result* SpatialCalculator::getResult(s32 index) const {
    if (index >= 0 && mResults.isBufferReady() && index < mResults.size())
        return mResults.get(index);
    return nullptr;
}

// 0x7100b8fe28
void SpatialCalculator::beginReferred() {
    ++mReferredCount;
}

// 0x7100b8fe38
void SpatialCalculator::endReferred() {
    if (mReferredCount - 1 >= 0)
        --mReferredCount;
}

// 0x7100b8fe4c
bool SpatialCalculator::isReferred() const {
    return mReferredCount != 0;
}

}  // namespace aal
