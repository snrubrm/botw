#include "Game/UI/euiMultiFilterWindowEx.h"
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

MultiFilterWindowEx::MultiFilterWindowEx(const MultiFilterWindowEx& other, LayoutEx* layout)
    : WindowEx(other) {
    auto* heap = GetNwAllocatorHeap();
    mFilter = new (heap, 8) FrameBufferMultiFilter;
    mFilter->initialize(heap, *this, layout);
}

MultiFilterWindowEx::~MultiFilterWindowEx() {
    if (mFilter) {
        delete mFilter;
        mFilter = nullptr;
    }
}

}  // namespace eui
