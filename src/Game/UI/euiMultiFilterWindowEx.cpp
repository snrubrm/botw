#include "Game/UI/euiMultiFilterWindowEx.h"
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

MultiFilterWindowEx::MultiFilterWindowEx(const nn::ui2d::ResWindow* resource,
                                       const nn::ui2d::ResWindow* replacement,
                                       const nn::ui2d::BuildArgSet& args)
    : WindowEx(resource, replacement, args) {
    auto* heap = GetNwAllocatorHeap();
    mFilter = new (heap, 8) FrameBufferMultiFilter;
    mFilter->initialize(heap, *this,
                       const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

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

void MultiFilterWindowEx::DrawSelf(nn::ui2d::DrawInfo& draw_info,
                                      nn::gfx::CommandBuffer& command_buffer) {
    auto& info = static_cast<DrawInfoEx&>(draw_info);
    if (info._100)
        return;
    const auto* texture = mFilter->captureAndFilter(*this, info);
    if (texture) {
        mFilter->applyTextureDataToWindowMaterial(this, &mTextureInfo, texture, info);
        Window::DrawSelf(draw_info, command_buffer);
        mFilter->freeResultTexture(texture);
    } else {
        Window::DrawSelf(draw_info, command_buffer);
    }
}

}  // namespace eui
