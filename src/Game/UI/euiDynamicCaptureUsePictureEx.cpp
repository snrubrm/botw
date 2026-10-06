#include "Game/UI/euiDynamicCaptureUsePictureEx.h"
#include <nn/ui2d/Layout.h>
#include "Game/UI/euiDynamicCapturePane.h"

namespace eui {

// 0x7100bf3378
DynamicCaptureUsePictureEx::DynamicCaptureUsePictureEx(const nn::ui2d::ResPicture* resource,
                                                       const nn::ui2d::ResPicture* resource2,
                                                       const nn::ui2d::BuildArgSet& args)
    : PictureEx(resource, resource2, args), mCapturePane(nullptr), mTextureIndex(0) {}

// 0x7100bf33b0
DynamicCaptureUsePictureEx::DynamicCaptureUsePictureEx(const DynamicCaptureUsePictureEx& other)
    : PictureEx(other), mCapturePane(other.mCapturePane), mTextureIndex(other.mTextureIndex) {}

// 0x7100bf33f4
void DynamicCaptureUsePictureEx::setCapture(DynamicCapturePane* capture_pane, u8 texture_index) {
    mCapturePane = capture_pane;
    mTextureIndex = texture_index;
}

void DynamicCaptureUsePictureEx::Calculate(nn::ui2d::DrawInfo& draw_info,
                                         nn::ui2d::Pane::CalculateContext& context,
                                         bool force_dirty) {
    if (mCapturePane)
        mCapturePane->applyTextureInfoToMaterialForCalculate(this, context.mLayout->GetLayoutSize(),
                                                            mTextureIndex);
    Picture::Calculate(draw_info, context, force_dirty);
}

}  // namespace eui
