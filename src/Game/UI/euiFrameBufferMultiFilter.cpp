#include "Game/UI/euiFrameBufferMultiFilter.h"
#include <utility/aglDynamicTextureAllocator.h>

namespace eui {

FrameBufferMultiFilter::FrameBufferMultiFilter() = default;

void FrameBufferMultiFilter::freeResultTexture(const agl::TextureData* texture) {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(texture);
}

}  // namespace eui
