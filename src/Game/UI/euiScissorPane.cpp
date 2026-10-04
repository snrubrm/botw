#include "Game/UI/euiScissorPane.h"

#include <common/aglDrawContext.h>
#include <gfx/seadFrameBuffer.h>
#include <gfx/seadViewport.h>
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100be1ea4
ScissorPane::ScissorPane(const nn::ui2d::ResPane* resource, const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Pane(resource, args) {}

// 0x7100be1ed4
ScissorPane::ScissorPane(const ScissorPane& other) : nn::ui2d::Pane(other) {}

// NON_MATCHING: base-position selection and clipping arithmetic are scheduled differently;
// the compiler also lowers the lower-bound clamps to floating-point maximum operations.
// 0x7100be1f04
void ScissorPane::Draw(nn::ui2d::DrawInfo& draw_info, nn::gfx::CommandBuffer& command_buffer) {
    auto& info = static_cast<DrawInfoEx&>(draw_info);
    if (!IsVisible() || !info._f8 || !GetGlobalAlpha()) {
        nn::ui2d::Pane::Draw(draw_info, command_buffer);
        return;
    }

    const auto* previous = info._f8;
    DrawInfoEx::RenderBufferInfo buffer_info = *previous;
    sead::Viewport viewport(*buffer_info.mFrameBuffer);
    buffer_info.mScissor = &viewport;

    const auto& size = GetSize();
    const auto& mtx = GetMtx();
    const f32 width = size.width * mtx.m[0][0];
    const f32 height = size.height * mtx.m[1][1];
    const f32 half_width = (width > 0 ? width : -width) * 0.5f;
    const f32 half_height = (height > 0 ? height : -height) * 0.5f;
    f32 x = mtx.m[0][3];
    f32 y = mtx.m[1][3];
    if (GetBasePositionH() == nn::ui2d::HorizontalPosition_Left)
        x += half_width;
    else if (GetBasePositionH() == nn::ui2d::HorizontalPosition_Right)
        x -= half_width;
    if (GetBasePositionV() == nn::ui2d::VerticalPosition_Top)
        y -= half_height;
    else if (GetBasePositionV() == nn::ui2d::VerticalPosition_Bottom)
        y += half_height;

    const auto& virtual_size = previous->mFrameBuffer->getVirtualSize();
    x += virtual_size.x * 0.5f;
    y += virtual_size.y * 0.5f;
    f32 left = x - half_width;
    f32 top = y - half_height;
    f32 right = x + half_width;
    f32 bottom = y + half_height;
    if (left < 0)
        left = 0;
    if (top < 0)
        top = 0;
    if (right > virtual_size.x)
        right = virtual_size.x;
    if (bottom > virtual_size.y)
        bottom = virtual_size.y;
    if (right - left >= virtual_size.x) {
        left = 0;
        right = virtual_size.x;
    }
    if (bottom - top >= virtual_size.y) {
        top = 0;
        bottom = virtual_size.y;
    }
    viewport.setMin({left, top});
    viewport.setMax({right, bottom});
    if (!viewport.isUndef()) {
        viewport.applyScissor(buffer_info.mDrawContext, *buffer_info.mFrameBuffer);
        info._f8 = &buffer_info;
        nn::ui2d::Pane::Draw(draw_info, command_buffer);
        info._f8 = previous;
        previous->mViewport->applyScissor(previous->mDrawContext, *previous->mFrameBuffer);
    }
}

}  // namespace eui
