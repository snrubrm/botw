#pragma once

#include "Game/UI/euiPictureEx.h"

namespace eui {

class DynamicCapturePane;

// Only the capture pointer and texture index are recovered; construction remains undeclared.
class DynamicCaptureUsePictureEx : public PictureEx {
public:
    NN_RUNTIME_TYPEINFO(PictureEx)

    DynamicCaptureUsePictureEx(const nn::ui2d::ResPicture* resource,
                               const nn::ui2d::ResPicture* resource2,
                               const nn::ui2d::BuildArgSet& args);
    DynamicCaptureUsePictureEx(const DynamicCaptureUsePictureEx& other);
    ~DynamicCaptureUsePictureEx() override = default;
    void Calculate(nn::ui2d::DrawInfo& draw_info, nn::ui2d::Pane::CalculateContext& context,
                   bool force_dirty) override;

    // 0x7100bf33f4 (placeholder name)
    void setCapture(DynamicCapturePane* capture_pane, u8 texture_index);

private:
    /* 0x108 */ DynamicCapturePane* mCapturePane;
    /* 0x110 */ u8 mTextureIndex;
};

}  // namespace eui
