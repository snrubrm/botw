#include "Game/UI/euiDynamicCapturePane.h"
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglMultiFilter.h>

namespace eui {

// 0x7100bf3214
void DynamicCapturePane::freeDynamicTexture() {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
    mTexture = nullptr;
}

}  // namespace eui
