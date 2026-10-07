#include "Game/UI/euiDynamicCapturePane.h"
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglMultiFilter.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiLayoutEx.h"

namespace eui {

DynamicCapturePane::DynamicCapturePane(const nn::ui2d::ResPane* resource,
                                       const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Pane(resource, args) {
    initialize_(const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

DynamicCapturePane::DynamicCapturePane(const DynamicCapturePane& other, LayoutEx* layout)
    : nn::ui2d::Pane(other) {
    initialize_(layout);
}

DynamicCapturePane::~DynamicCapturePane() {
    if (mClearColor) {
        delete mClearColor;
        mClearColor = nullptr;
    }
}

// 0x7100bf3214
void DynamicCapturePane::freeDynamicTexture() {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
    mTexture = nullptr;
}

}  // namespace eui
