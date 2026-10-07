#include "Game/UI/euiMultiFilterPictureEx.h"
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

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
void MultiFilterPictureEx::DrawSelf(nn::ui2d::DrawInfo& draw_info,
                                      nn::gfx::CommandBuffer& command_buffer) {
    auto& info = static_cast<DrawInfoEx&>(draw_info);
    if (info._100)
        return;
    const auto* texture = mFilter->captureAndFilter(*this, info);
    if (texture) {
        mFilter->applyTextureDataToPictureMaterial(this, &mTextureInfo, texture, info);
        Picture::DrawSelf(draw_info, command_buffer);
        mFilter->freeResultTexture(texture);
    } else {
        Picture::DrawSelf(draw_info, command_buffer);
    }
}

}  // namespace eui
