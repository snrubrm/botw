#pragma once

#include "Game/UI/euiPictureEx.h"

namespace eui {

class DynamicCapturePane;

// Only the capture pointer and texture index are recovered; construction remains undeclared.
class DynamicCaptureUsePictureEx : public PictureEx {
public:
    NN_RUNTIME_TYPEINFO(PictureEx)

    ~DynamicCaptureUsePictureEx() override;
    void Calculate(nn::ui2d::DrawInfo& draw_info, nn::ui2d::Pane::CalculateContext& context,
                   bool force_dirty) override;

private:
    /* 0x108 */ DynamicCapturePane* mCapturePane;
    /* 0x110 */ u8 mTextureIndex;
};

}  // namespace eui
