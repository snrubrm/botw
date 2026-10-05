#include "Game/UI/euiScreen.h"
#include <common/aglDrawContext.h>
#include <gfx/seadFrameBuffer.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadViewport.h>

namespace eui {

// 0x7100bf2ab0
void DrawInfoEx::freeDynamicTexture() {
    for (auto it = mDynamicTextures.begin(); it != mDynamicTextures.end();) {
        const auto current = it++;
        current->freeDynamicTexture();
        mDynamicTextures.erase(current);
    }
}

// 0x7100bf2b1c
void DrawInfoEx::applyRenderBufferInfo(const RenderBufferInfo* info) {
    info->mFrameBuffer->bind(info->mDrawContext);
    if (info->mScissor) {
        info->mViewport->applyViewport(info->mDrawContext, *info->mFrameBuffer);
        info->mScissor->applyScissor(info->mDrawContext, *info->mFrameBuffer);
    } else {
        info->mViewport->apply(info->mDrawContext, *info->mFrameBuffer);
    }
    info->mGraphicsContext->apply(info->mDrawContext);
}

}  // namespace eui
