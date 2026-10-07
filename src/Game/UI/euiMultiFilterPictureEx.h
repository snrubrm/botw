#pragma once

#include <nn/ui2d/TextureInfo.h>
#include "Game/UI/euiPictureEx.h"

namespace eui {
class FrameBufferMultiFilter;
class LayoutEx;

class MultiFilterPictureEx : public PictureEx {
public:
    NN_RUNTIME_TYPEINFO(PictureEx)
    MultiFilterPictureEx(const nn::ui2d::ResPicture*, const nn::ui2d::ResPicture*,
                         const nn::ui2d::BuildArgSet&);
    MultiFilterPictureEx(const MultiFilterPictureEx&, LayoutEx*);
    ~MultiFilterPictureEx() override;
    void DrawSelf(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;

private:
    /* 0x108 */ FrameBufferMultiFilter* mFilter;
    /* 0x110 */ nn::ui2d::ExternalTextureInfo mTextureInfo;
};
}  // namespace eui
