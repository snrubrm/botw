#include <cstring>
#include "gsys/gsysModelRenderCache.h"
#include <common/aglDrawContext.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <cull/aglOcclusionQuery.h>
#include <nvn/nvn_FuncPtrInline.h>
#include "gsys/gsysG3dResShaderProgramEx.h"
#include "gsys/gsysModelAssignRenderInfo.h"
#include "gsys/gsysModelRenderContext.h"
#include "gsys/gsysModelRenderUnitNW.h"
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
        _148 = -1;
    }
}

void ModelRenderCache::setForceBlendColor(const sead::Color4f& color) {
    mForceBlendColor.r = color.r * color.a;
    mForceBlendColor.g = color.g * color.a;
    mForceBlendColor.b = color.b * color.a;
    mForceBlendColor.a = color.a;
}

// 0x7100c80100
// NON_MATCHING: clang if-converts the two-instruction second blend-factor arm into csinc/csel
// where the original branches; the original's arms also each end with the loop's first sampler
// store, which only a branchy arm produces. Every other instruction sequence follows.
ModelRenderCache::ModelRenderCache(agl::DrawContext* draw_context,
                                   const ModelRenderContext* context,
                                   sead::BitFlag32 flags, u32 a4,
                                   ModelEnum::ShaderAssignType type, u32 a6, u32 a7,
                                   u32 a8, u32 a9, ModelRenderStatistics* statistics)
    : _0(a6),
      _4(flags),
      _8(a4),
      _c(a9),
      mContext(context),
      mDrawContext(draw_context),
      mViewIndex(context->getViewIndex()),
      mShaderAssignType(static_cast<u8>(type)),
      _22(a7),
      _23(0),
      mRenderUBO(nullptr),
      _32(0xff),
      _33(0xff),
      _36(0),
      _38(0xff),
      mPassViewProjIndex(0xff),
      mChannelMask(0),
      mForceBlendColor(0, 0, 0, 0),
      mOcclusionQuery(nullptr),
      _1c0(0),
      _240(0),
      _248(0),
      _24c(-1),
      mStatistics(statistics) {
    mGraphicsContext.setDepthTestEnable(true);
    mBlendMask = 0;
    mGraphicsContext.setDepthWriteEnable(1);
    mGraphicsContext.setDepthFuncMaybe(4, 5);

    const u32 flag_bits = _0;
    u8 src;
    u8 dst;
    if ((flag_bits & 0x1000) != 0 || (a7 & 0x30) != 0) {
        _36 |= 0x40;
        src = 0x61;
        dst = 0x64;
    } else if ((flag_bits & 0x400) != 0) {
        src = 9;
        dst = 1;
    } else {
        src = 5;
        dst = 6;
    }

    for (s32 i = 0; i < 8; ++i)
        mGraphicsContext.setBlendControl(i, src, src, dst, dst, 1, 1);

    mGraphicsContext.setBlendEnableMask(0);
    mGraphicsContext.setUnk2Maybe(0);
    mGraphicsContext.setBlendAlphaMaybe(0.5f);

    const u8 type_value = mShaderAssignType;
    u32 blend_bits = (flag_bits & 0x100) != 0 ? 0 : 1;
    u32 other_bits = 1;
    switch (type_value) {
    case 1:
    case 8:
        blend_bits = 0;
        other_bits = 0;
        break;
    case 3:
        other_bits = 0;
        break;
    }
    blend_bits |= (flag_bits & 0x2000) >> 13;
    other_bits |= (flag_bits & 0x4000) >> 14;

    const u32 blend_nibble = blend_bits != 0 ? 7u : 0u;
    const u32 other_nibble = other_bits != 0 ? 8u : 0u;
    const u32 nibble = blend_nibble | other_nibble;
    u32 replicated = nibble;
    replicated |= replicated << 4;
    replicated |= nibble << 8;
    replicated |= nibble << 12;
    replicated |= nibble << 16;
    replicated |= nibble << 20;
    replicated |= nibble << 24;
    replicated |= nibble << 28;
    mChannelMask = replicated & a8;

    if ((flag_bits & 0x80000) != 0)
        _36 |= 0x20;
    else
        _36 &= ~u16(0x20);

    memcpy(mTextureSamplers, mContext->mPassTextures, sizeof(mTextureSamplers));
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

// 0x7100c80ff4
void ModelRenderCache::loadResShaderProgram_(const ModelRenderUnitNW& unit,
                                             const ModelAssignRenderInfo& info) {
    G3dResShaderProgramEx* program = info.mShaderProgram.mEx;
    mShaderProgram = program;
    program->load(mDrawContext, info.mShaderProgram.mResShaderProgram,
                  agl::ShaderOptimizeType(_23), false);

    if (program->mProgramId != _148) {
        _148 = program->mProgramId;
        _14c[3] = program->mUniformBlockLocations[3].getLocation();
        _14c[5] = program->mUniformBlockLocations[5].getLocation();

        const agl::ShaderLocation& uniform_location = program->mUniformBlockLocations[1];
        const agl::ShaderLocation& scene_material_location = program->mUniformBlockLocations[10];

        if (_14c[1] != uniform_location.getLocation()) {
            _14c[1] = uniform_location.getLocation();
            agl::UniformBlock* block = mRenderUBO;
            agl::DrawContext* draw_context = mDrawContext;
            block->setUniform(draw_context, block->getGPUAddressMaybe(), uniform_location, 0,
                              block->getBlockSizeMaybe());
        }

        if (_14c[10] != scene_material_location.getLocation()) {
            _14c[10] = scene_material_location.getLocation();
            mContext->mShaderContext->loadSceneMaterial(mDrawContext, scene_material_location);
        }

        if (_14c[6] != program->mUniformBlockLocations[6].getLocation()) {
            _14c[6] = program->mUniformBlockLocations[6].getLocation();
            _34 = 0xff;
        }
    }

    if (program->mRenderState != _40) {
        _40 = program->mRenderState;
        const u32 mask = program->mTextureMask;
        if (mask & 0x1fffffff) {
            const agl::ShaderLocation* sampler_location = program->mSamplerLocations;
            for (s32 i = 0; i < 29; ++i, ++sampler_location) {
                if (mask & (1u << i))
                    mTextureSamplers[i]->activate(mDrawContext, *sampler_location, 0, true);
            }        }
    }
}

// 0x7100c80694
// NON_MATCHING: instruction sequence is the same; only the register assignment of the loaded
// polygon-offset byte and of the face shift differs.
void ModelRenderCache::setGraphicsContextToPolygonCtrl(sead::GraphicsContext* context, u32 flags) {
    context->setPolygonOffsetEnable((flags & 4) != 0);

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
    context->setCullFace(cull_face);

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
    context->setPolygonMode(polygon_mode, polygon_mode);
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
    mShaderProgram = nullptr;
    _1b8 = 0;
    _40 = -1;
    _148 = -1;
    for (s32 i = 0; i < 15; ++i)
        _14c[i] = -1;
}

}  // namespace gsys
