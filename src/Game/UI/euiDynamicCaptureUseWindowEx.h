#pragma once

#include "Game/UI/euiWindowEx.h"

namespace eui {

class DynamicCapturePane;

// The window twin of DynamicCaptureUsePictureEx: draws the texture of a DynamicCapturePane.
class DynamicCaptureUseWindowEx : public WindowEx {
public:
    NN_RUNTIME_TYPEINFO(WindowEx)

    DynamicCaptureUseWindowEx(const nn::ui2d::ResWindow* resource,
                              const nn::ui2d::ResWindow* resource2,
                              const nn::ui2d::BuildArgSet& args);
    DynamicCaptureUseWindowEx(const DynamicCaptureUseWindowEx& other);
    ~DynamicCaptureUseWindowEx() override = default;

    void Calculate(nn::ui2d::DrawInfo& draw_info, nn::ui2d::Pane::CalculateContext& context,
                   bool force_dirty) override;
    void DrawSelf(nn::ui2d::DrawInfo& draw_info, nn::gfx::CommandBuffer& command_buffer) override;

    // 0x7100bf3678 (placeholder name)
    void setCapture(DynamicCapturePane* capture_pane, u8 texture_index);

private:
    // The Window members (0xe0 - 0x138) are not recovered.
    u8 _e0[0x138 - 0xe0];
    /* 0x138 */ DynamicCapturePane* mCapturePane;
    /* 0x140 */ u8 mTextureIndex;
};

}  // namespace eui
