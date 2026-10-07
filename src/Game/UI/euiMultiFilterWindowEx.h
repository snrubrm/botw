#pragma once

#include <nn/ui2d/TextureInfo.h>
#include "Game/UI/euiWindowEx.h"

namespace eui {

class FrameBufferMultiFilter;
class LayoutEx;

class MultiFilterWindowEx : public WindowEx {
public:
    NN_RUNTIME_TYPEINFO(WindowEx)
    MultiFilterWindowEx(const nn::ui2d::ResWindow*, const nn::ui2d::ResWindow*,
                        const nn::ui2d::BuildArgSet&);
    MultiFilterWindowEx(const MultiFilterWindowEx& other, LayoutEx* layout);
    ~MultiFilterWindowEx() override;
    void DrawSelf(nn::ui2d::DrawInfo& draw_info, nn::gfx::CommandBuffer& command_buffer) override;

private:
    /* 0x138 */ FrameBufferMultiFilter* mFilter = nullptr;
    /* 0x140 */ nn::ui2d::ExternalTextureInfo mTextureInfo;
};

}  // namespace eui
