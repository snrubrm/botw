#include "Game/UI/euiDynamicCaptureUsePictureEx.h"
#include <nn/ui2d/Layout.h>
#include "Game/UI/euiDynamicCapturePane.h"

namespace eui {

void DynamicCaptureUsePictureEx::Calculate(nn::ui2d::DrawInfo& draw_info,
                                         nn::ui2d::Pane::CalculateContext& context,
                                         bool force_dirty) {
    if (mCapturePane)
        mCapturePane->applyTextureInfoToMaterialForCalculate(this, context.mLayout->GetLayoutSize(),
                                                            mTextureIndex);
    Picture::Calculate(draw_info, context, force_dirty);
}

}  // namespace eui
