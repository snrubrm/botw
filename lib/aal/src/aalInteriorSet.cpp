#include "aal/aalInteriorSet.h"
#include <algorithm>
#include "aal/aalInterior.h"

namespace aal {

// 0x7100b85ac8
InteriorSet::InteriorSet() : mCurrentIndex(-1) {}

// 0x7100b85ae8 (D1) / 0x7100b85b68 (D0)
InteriorSet::~InteriorSet() {
    for (s32 i = 0; i < mInteriors.size(); ++i) {
        if (Interior* interior = mInteriors.at(i))
            delete interior;
    }
    mInteriors.freeBuffer();
}

// 0x7100b85bf0
void InteriorSet::initialize(const sead::Buffer<InteriorType>& types, sead::Heap* heap) {
    mInteriors.allocBuffer(std::max(types.size(), 1), heap, 8);
    if (mInteriors.isBufferReady() && mInteriors.size() == 0) {
        for (InteriorType type : types)
            mInteriors.pushBack(Interior::create(type, heap));
    }
}

// 0x7100b85c90
Interior* InteriorSet::getInterior(s32 index) const {
    if (!mInteriors.isBufferReady())
        return nullptr;
    if (mInteriors.size() == 0)
        return nullptr;
    s32 idx = mCurrentIndex >= 0 ? mCurrentIndex : index;
    if (idx >= mInteriors.size())
        idx = 0;
    return mInteriors.at(idx);
}

// 0x7100b85cdc
s32 InteriorSet::getNumOfInterior() const {
    return mInteriors.isBufferReady() ? mInteriors.size() : 0;
}

// 0x7100b85cf4
void InteriorSet::setInteriorSize(f32 size) {
    for (s32 i = 0; i < mInteriors.size(); ++i) {
        if (Interior* interior = mInteriors.at(i))
            interior->setInteriorSize(size);
    }
}

}  // namespace aal
