#pragma once

#include <cstddef>
#include <nn/ui2d/Pane.h>

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
};
static_assert(offsetof(DynamicCapturePane, mDynamicTextureNode) == 0xe0);

}  // namespace eui
