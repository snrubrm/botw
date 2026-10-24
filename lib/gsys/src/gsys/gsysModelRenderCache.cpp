#include "gsys/gsysModelRenderCache.h"
#include <common/aglDrawContext.h>
#include <cull/aglOcclusionQuery.h>
#include <nvn/nvn_FuncPtrInline.h>
#include "gsys/gsysModelRenderContext.h"
#include "gsys/gsysShaderContext.h"

namespace gsys {

void ModelRenderCache::setBlendMask(u32 mask) {
    mBlendMask = mask;
}

void ModelRenderCache::setChannelMask(u32 mask) {
    mChannelMask = mask;
}

void ModelRenderCache::setPassViewProjIndex(int index) {
    if (mPassViewProjIndex != index) {
        mPassViewProjIndex = index;
        mRenderUBO = mContext->mShaderContext->getContextRenderUBO(mPassViewProjIndex);
        _148[0] = -1;
    }
}

void ModelRenderCache::setForceBlendColor(const sead::Color4f& color) {
    mForceBlendColor.r = color.r * color.a;
    mForceBlendColor.g = color.g * color.a;
    mForceBlendColor.b = color.b * color.a;
    mForceBlendColor.a = color.a;
}

// 0x7100c803f4
ModelRenderCache::~ModelRenderCache() {
    if (mOcclusionQuery) {
        nvnCommandBufferSetRenderEnable(
            mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer, true);
        mOcclusionQuery = nullptr;
    }
}

// 0x7100c80438
void ModelRenderCache::loadOcclusionQuery(const agl::cull::OcclusionQuery* query) {
    if (mOcclusionQuery == query)
        return;

    if (mOcclusionQuery) {
        nvnCommandBufferSetRenderEnable(
            mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer, true);
    }

    if (query) {
        if (sead::BitFlag16(sead::BitFlag16::makeMask(mViewIndex)).isOn(query->getViewMask())) {
            nvnCommandBufferSetRenderEnableConditional(
                mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer,
                NVN_CONDITIONAL_RENDER_MODE_RENDER_IF_NOT_EQUAL,
                nvnBufferGetAddress(&query->getBuffer()) + (query->getIndex() << 5));
        } else {
            query = nullptr;
        }
    }

    mOcclusionQuery = query;
}

// 0x7100c80574: releases the occlusion query and returns the render state to its defaults.
// NON_MATCHING: one redundant u8 mask (and w8, w10, #0xff) before the polygon-mode table is
// missing, and the +0x40 store is scheduled after the +0x1b0 pair.
void ModelRenderCache::reset() {
    if (mOcclusionQuery) {
        nvnCommandBufferSetRenderEnable(
            mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer, true);
        mOcclusionQuery = nullptr;
    }

    const u32 flags = _22 | _31;
    mGraphicsContext.setPolygonOffsetEnable((flags & 4) != 0);

    const u32 face = flags & 8;
    u32 cull_face;
    switch (flags & 3) {
    case 0:
        cull_face = (face >> 3) + 1;
        break;
    case 1:
        cull_face = 2 - (face >> 3);
        break;
    case 2:
        cull_face = 0;
        break;
    case 3:
        cull_face = 3;
        break;
    }
    mGraphicsContext.setCullFace(cull_face);

    u32 polygon_mode;
    switch ((static_cast<u8>(flags) >> 4) & 3) {
    case 0:
        polygon_mode = 2;
        break;
    case 1:
        polygon_mode = 1;
        break;
    case 2:
        polygon_mode = 0;
        break;
    default:
        polygon_mode = 2;
        break;
    }
    mGraphicsContext.setPolygonMode(polygon_mode, polygon_mode);

    if (!(_0 & 0x8000))
        mGraphicsContext.apply(mDrawContext);

    _32 = 0xff;
    _34 = 0xff;
    _30 = 8;
    _1a8 = 0;
    _1b0 = 0;
    _1b8 = 0;
    _40 = -1;
    for (s32 i = 0; i < 16; ++i)
        _148[i] = -1;
}

}  // namespace gsys
