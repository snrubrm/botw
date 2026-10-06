#include "Game/UI/euiDynamicCaptureUseWindowEx.h"
#include <nn/ui2d/Layout.h>
#include "Game/UI/euiDynamicCapturePane.h"
#include "Game/UI/euiTypes.h"

namespace eui {

// 0x7100bf35fc
DynamicCaptureUseWindowEx::DynamicCaptureUseWindowEx(const nn::ui2d::ResWindow* resource,
                                                     const nn::ui2d::ResWindow* resource2,
                                                     const nn::ui2d::BuildArgSet& args)
    : WindowEx(resource, resource2, args), mCapturePane(nullptr), mTextureIndex(0) {}

// 0x7100bf3634
DynamicCaptureUseWindowEx::DynamicCaptureUseWindowEx(const DynamicCaptureUseWindowEx& other)
    : WindowEx(other), mCapturePane(other.mCapturePane), mTextureIndex(other.mTextureIndex) {}

// 0x7100bf3678
void DynamicCaptureUseWindowEx::setCapture(DynamicCapturePane* capture_pane, u8 texture_index) {
    mCapturePane = capture_pane;
    mTextureIndex = texture_index;
}

// 0x7100bf3684
void DynamicCaptureUseWindowEx::Calculate(nn::ui2d::DrawInfo& draw_info,
                                          nn::ui2d::Pane::CalculateContext& context,
                                          bool force_dirty) {
    if (mCapturePane)
        mCapturePane->applyTextureInfoToMaterialForCalculate(
            this, context.mLayout->GetLayoutSize(), mTextureIndex);
    Window::Calculate(draw_info, context, force_dirty);
}

// 0x7100bf36e0 (the CSV attributes it to DynamicCaptureUsePictureEx)
void DynamicCaptureUseWindowEx::DrawSelf(nn::ui2d::DrawInfo& draw_info,
                                         nn::gfx::CommandBuffer& command_buffer) {
    if (mCapturePane && mCapturePane->mTexture) {
        ApplyTextureInfoToMaterial(this, mCapturePane->mTextureInfo, mTextureIndex);
        Window::DrawSelf(draw_info, command_buffer);
    }
}

}  // namespace eui
