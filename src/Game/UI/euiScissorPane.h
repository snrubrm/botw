#pragma once

#include <nn/ui2d/Pane.h>

namespace eui {

// The resource and copy constructors add only the derived vtable; the
// LayoutEx factory allocates the same 0xe0 bytes as an ordinary Pane.
class ScissorPane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    ScissorPane(const nn::ui2d::ResPane*, const nn::ui2d::BuildArgSet&);
    ScissorPane(const ScissorPane&);
    ~ScissorPane() override = default;

    void Draw(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;
};

}  // namespace eui
