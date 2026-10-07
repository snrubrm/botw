#include "Game/UI/euiMultiFilterPictureEx.h"
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {
MultiFilterPictureEx::MultiFilterPictureEx(const nn::ui2d::ResPicture* resource,
                                         const nn::ui2d::ResPicture* replacement,
                                         const nn::ui2d::BuildArgSet& args)
    : PictureEx(resource, replacement, args), mFilter(nullptr) {
    auto* heap = GetNwAllocatorHeap();
    mFilter = new (heap, 8) FrameBufferMultiFilter;
    mFilter->initialize(heap, *this,
                       const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

MultiFilterPictureEx::MultiFilterPictureEx(const MultiFilterPictureEx& other, LayoutEx* layout)
    : PictureEx(other) {
    auto* heap = GetNwAllocatorHeap();
    mFilter = new (heap, 8) FrameBufferMultiFilter;
    mFilter->initialize(heap, *this, layout);
}

MultiFilterPictureEx::~MultiFilterPictureEx() {
    if (mFilter) {
        delete mFilter;
        mFilter = nullptr;
    }
}
}  // namespace eui
