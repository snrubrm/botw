#pragma once

#include <cstddef>
#include <prim/seadBitFlag.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/TextureInfo.h>

namespace agl {
class TextureData;
namespace utl {
class MultiFilter;
}
}  // namespace agl

namespace eui {

class LayoutEx;

// The resource and copy constructors establish the capture node, clear color,
// texture reference and owned render objects.
class DynamicCapturePane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)
    DynamicCapturePane(const nn::ui2d::ResPane*, const nn::ui2d::BuildArgSet&);
    DynamicCapturePane(const DynamicCapturePane&, LayoutEx*);
    ~DynamicCapturePane() override;
    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    void Draw(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;
    void initialize_(LayoutEx*);
    void freeDynamicTexture();
    void applyTextureInfoToMaterialForCalculate(nn::ui2d::Pane* pane,
                                               const nn::ui2d::Size& size, s32 texture_index);

    /* 0xe0 */ nn::util::IntrusiveListNode mDynamicTextureNode;
    /* 0xf0 */ sead::BitFlag<u8> mCaptureFlags;
    /* 0xf8 */ sead::Color4f* mClearColor = nullptr;
    /* 0x100 */ agl::utl::MultiFilter* mMultiFilter = nullptr;  // filter whose result texture the pane displays (may be null)
    /* 0x108 */ nn::ui2d::ExternalTextureInfo mTextureInfo;
    /* 0x120 */ const agl::TextureData* mTexture = nullptr;  // the capture's texture data (null until captured)
    /* 0x128 */ agl::RenderBuffer mRenderBuffer;
    /* 0x190 */ agl::RenderTargetColor mRenderTarget;
};
static_assert(offsetof(DynamicCapturePane, mDynamicTextureNode) == 0xe0);
static_assert(sizeof(DynamicCapturePane) == 0x308);

}  // namespace eui
