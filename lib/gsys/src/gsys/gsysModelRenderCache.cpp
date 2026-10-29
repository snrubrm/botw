#include <cstring>
#include "gsys/gsysModelRenderCache.h"
#include <common/aglDrawContext.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <cull/aglOcclusionQuery.h>
#include <g3d/aglShaderUtilG3D.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <nn/g3d/ModelObj.h>
#include <nn/g3d/SkeletonObj.h>
#include "gsys/gsysG3dResMaterialEx.h"
#include "gsys/gsysG3dResShaderProgramEx.h"
#include "gsys/gsysG3dResShapeEx.h"
#include "gsys/gsysModelAssignRenderInfo.h"
#include "gsys/gsysModelRenderContext.h"
#include "gsys/gsysModelNW.h"
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

// 0x7100c809ac
// NON_MATCHING: the blend-colour and depth-state copies use narrower stores and the recorded-command
// path is laid out differently; the shape, material and shader records themselves are modelled.
bool ModelRenderCache::loadResource(const ModelRenderUnitNW* unit) {
    const G3dResShapeEx* shape_ex = unit->mResShapeEx;

    s32 assign_type = _38;
    if (_38 == -1)
        assign_type = unit->getShaderVariation(mShaderAssignType);

    const s32 variation_index = assign_type + mShaderAssignType * 4;
    const ModelAssignRenderInfo* info = unit->mShapeRenderInfos[variation_index];
    if (!info->mShaderProgram.mResShaderProgram)
        return false;

    if (info->mShaderProgram.mEx != mShaderProgram) {
        loadResShaderProgram_(*unit, *info);
        _1a8 = nullptr;
    }

    if (_1a8 != shape_ex) {
        _1a8 = shape_ex;

        u16 flags = _36;
        if (flags & 2) {
            G3dResMaterialEx* material = unit->mResMaterialEx;
            G3dResMaterialEx::RenderState& state = material->mRenderState;
            if (&state != _1b8) {
                if (state.mType == 5 || state.mType == 2) {
                    if (state.mBlendTargetCount == 0) {
                        mGraphicsContext.setBlendEnableMask(0);
                    } else {
                        mGraphicsContext.setBlendEnableMask(mBlendMask);
                        mGraphicsContext.setBlendColor(state.mBlendColor);
                        for (s32 i = 0; i < 8; ++i) {
                            const sead::GraphicsContext::BlendControl& control =
                                state.mBlendControl[i];
                            mGraphicsContext.setBlendControl(
                                i, control.src_rgb, control.src_alpha, control.dst_rgb,
                                control.dst_alpha, control.equation_rgb, control.equation_alpha);
                        }
                    }

                    if (state.mType == 5 && (flags & 0x10)) {
                        mGraphicsContext.setDepthTestEnable(state.mDepthTestEnable);
                        mGraphicsContext.setDepthWriteEnable(state.mDepthWriteEnable);
                        mGraphicsContext.setDepthFunc(state.mDepthFunc);
                    }
                }

                flags |= 0x80;
                _1b8 = &state;
                _36 = flags;
            }
        }

        if (!(flags & 0x20) || !(info->_10 & 1)) {
            shape_ex->activateResource(mDrawContext, unit->mResMaterialEx,
                                       ModelEnum::ShaderAssignType(mShaderAssignType), assign_type);
        } else if (info->_10 & 2) {
            nvnCommandBufferCallCommands(
                mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer, 1,
                &info->mCommandHandle);
        }
    }

    const u16 flags = _36;
    const u32 buffer_index = static_cast<const ModelNW*>(unit->mModelUnit)->_168 & 3;
    if (!(flags & 0x20) || !info->mDisplayLists[buffer_index].isActiveMaybe()) {
        const G3dResShapeEx::ShaderRecord& record =
            shape_ex->mShaderRecords[assign_type + mShaderAssignType * 4];
        unit->activateInstance(mDrawContext, record.mShaderProgram, record.mSampler, mViewIndex,
                               buffer_index);
    } else if (info->mDisplayLists[buffer_index].hasRecordedCommands()) {
        const agl::DisplayList& list = info->mDisplayLists[buffer_index];
        nvnCommandBufferCallCommands(
            mDrawContext->getCommandBuffer()->ToData()->pNvnCommandBuffer, 1,
            &list.getCommandHandle());

        if (mViewIndex != 0 && (unit->mFlags32 & 2)) {
            const nn::g3d::ShapeObj* shape = unit->getShape();
            const nn::gfx::Buffer* buffer = nullptr;
            if (shape->_8_flags & 1) {
                if (shape->m_d == 0) {
                    if (shape->mBuffers)
                        buffer = &shape->mBuffers[buffer_index];
                } else if (shape->mBuffers) {
                    buffer = &shape->mBuffers[buffer_index + shape->m_f * mViewIndex];
                }
            }
            agl::g3d::ShaderUtilG3D::load(mDrawContext, mShaderProgram->mUniformBlockLocations[4],
                                          *buffer, 0x100, buffer_index);
        }
    }

    if (unit->mPolygonCtrl != _31) {
        const u8 polygon_flags = _22 | unit->mPolygonCtrl;
        const u8 face_flags = polygon_flags & 8;
        const u32 mode = polygon_flags & 3;

        mGraphicsContext.setPolygonOffsetEnable((polygon_flags & 4) != 0);

        u8 cull_face;
        switch (mode) {
        case 1:
            cull_face = 2 - (face_flags >> 3);
            break;
        case 2:
            cull_face = 0;
            break;
        case 3:
            cull_face = 3;
            break;
        default:
            cull_face = (face_flags >> 3) + 1;
            break;
        }
        mGraphicsContext.setCullFace(cull_face);

        const u8 packed = u8(0x1020200 >> ((polygon_flags >> 1 & 0x18) ^ 0x10));
        mGraphicsContext.setPolygonMode(packed, packed);

        _36 |= 0x80;
        _31 = unit->mPolygonCtrl;
    }

    if (unit->_232 != 0) {
        if (unit->_232 & 1) {
            agl::UniformBlock* block = static_cast<const ModelNW*>(unit->mModelUnit)->_70[0];
            block->setUniform(mDrawContext, block->getGPUAddressMaybe(),
                              mShaderProgram->mUniformBlockLocations[11], 0,
                              block->getBlockSizeMaybe());
        }
        if (unit->_232 & 2) {
            agl::UniformBlock* block = static_cast<const ModelNW*>(unit->mModelUnit)->_70[1];
            block->setUniform(mDrawContext, block->getGPUAddressMaybe(),
                              mShaderProgram->mUniformBlockLocations[12], 0,
                              block->getBlockSizeMaybe());
        }
        if (unit->_232 & 4) {
            agl::UniformBlock* block = static_cast<const ModelNW*>(unit->mModelUnit)->_70[2];
            block->setUniform(mDrawContext, block->getGPUAddressMaybe(),
                              mShaderProgram->mUniformBlockLocations[13], 0,
                              block->getBlockSizeMaybe());
        }
    }

    if (unit->_31 != _34 && _14c[6].getLocation() != -1 &&
        mContext->mEnvObjSetMgr != nullptr) {
        agl::UniformBlock* block = mContext->mShaderContext->getEnvUBO(
            mContext->mEnvObjSetMgr, s8(unit->_31));
        block->setUniform(mDrawContext, block->getGPUAddressMaybe(), _14c[6], 0,
                          block->getBlockSizeMaybe());
        _34 = unit->_31;
    }

    if (_0 & 0x100000) {
        const u8 index = static_cast<const ModelNW*>(unit->mModelUnit)->_203;
        const nn::g3d::SkeletonObj* skeleton =
            static_cast<const ModelNW*>(unit->mModelUnit)->getSkeletonObj();
        const nn::gfx::Buffer* skeleton_buffer = nullptr;
        if (skeleton->GetBuffersMaybe())
            skeleton_buffer = &skeleton->GetBuffersMaybe()[index];
        agl::g3d::ShaderUtilG3D::load(mDrawContext, _14c[3], *skeleton_buffer,
                                      skeleton->GetBufferSizeMaybe(), index);

        const nn::g3d::ShapeObj* shape = unit->getShape();
        const nn::gfx::Buffer* shape_buffer = nullptr;
        if (shape->_8_flags & 1) {
            if (shape->m_d == 0) {
                if (shape->mBuffers)
                    shape_buffer = &shape->mBuffers[index];
            } else if (shape->mBuffers) {
                shape_buffer = &shape->mBuffers[index + shape->m_f * mViewIndex];
            }
        }
        agl::g3d::ShaderUtilG3D::load(mDrawContext, _14c[5], *shape_buffer, 0x100, index);
    }

    if (_36 & 0x80) {
        if ((_0 & 0x8000) == 0)
            mGraphicsContext.apply(mDrawContext);
        _36 &= ~u16(0x80);
    }

    return true;
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
        _14c[3] = program->mUniformBlockLocations[3];
        _14c[5] = program->mUniformBlockLocations[5];

        const agl::ShaderLocation& uniform_location = program->mUniformBlockLocations[1];
        const agl::ShaderLocation& scene_material_location = program->mUniformBlockLocations[10];

        if (_14c[1].getLocation() != uniform_location.getLocation()) {
            _14c[1] = uniform_location;
            agl::UniformBlock* block = mRenderUBO;
            agl::DrawContext* draw_context = mDrawContext;
            block->setUniform(draw_context, block->getGPUAddressMaybe(), uniform_location, 0,
                              block->getBlockSizeMaybe());
        }

        if (_14c[10].getLocation() != scene_material_location.getLocation()) {
            _14c[10] = scene_material_location;
            mContext->mShaderContext->loadSceneMaterial(mDrawContext, scene_material_location);
        }

        if (_14c[6].getLocation() != program->mUniformBlockLocations[6].getLocation()) {
            _14c[6] = program->mUniformBlockLocations[6];
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
        _14c[i] = agl::ShaderLocation(-1);
}

// 0x7100c81184
// NON_MATCHING: same instructions in a different order (the vtable store and the +0x10 zero
// store swap places, and the member address is rematerialised); register/schedule only.
ModelRenderState::ModelRenderState() {}

// 0x7100c811b8
ModelRenderState::~ModelRenderState() {}

}  // namespace gsys
