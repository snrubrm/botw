#pragma once

#include <cstddef>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/TextureInfo.h>

namespace agl {
class TextureData;
namespace utl {
class MultiFilter;
}
}  // namespace agl

namespace eui {

// Known prefix only: the resource constructor initializes this node after
// Pane, and DrawInfoEx removes it after freeing the dynamic texture. The
// remaining capture state and allocation extent are not modeled here.
class DynamicCapturePane : public nn::ui2d::Pane {
public:
    void freeDynamicTexture();
    void applyTextureInfoToMaterialForCalculate(nn::ui2d::Pane* pane,
                                               const nn::ui2d::Size& size, s32 texture_index);

    /* 0xe0 */ nn::util::IntrusiveListNode mDynamicTextureNode;
    u8 _f0[0x100 - 0xf0];
    /* 0x100 */ agl::utl::MultiFilter* mMultiFilter;  // filter whose result texture the pane displays (may be null)
    /* 0x108 */ nn::ui2d::ExternalTextureInfo mTextureInfo;
    /* 0x120 */ const agl::TextureData* mTexture;  // the capture's texture data (null until captured)
};
static_assert(offsetof(DynamicCapturePane, mDynamicTextureNode) == 0xe0);

}  // namespace eui
