#include "Game/UI/euiDynamicCapturePane.h"
#include "Game/UI/euiCapturePane.h"
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiTypes.h"
#include <common/aglDrawContext.h>
#include <common/aglTextureSampler.h>
#include <utility/aglImageFilter2D.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadViewport.h>
#include <nn/ui2d/ResExtUserData.h>
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglMultiFilter.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiLayoutEx.h"
#include <cstring>
#include <gfx/seadProjection.h>
#include <nn/ui2d/DrawInfo.h>

namespace eui {

DynamicCapturePane::DynamicCapturePane(const nn::ui2d::ResPane* resource,
                                       const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Pane(resource, args) {
    initialize_(const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

DynamicCapturePane::DynamicCapturePane(const DynamicCapturePane& other, LayoutEx* layout)
    : nn::ui2d::Pane(other) {
    initialize_(layout);
}

// 0x7100bf2bec
void DynamicCapturePane::initialize_(LayoutEx* layout) {
    auto* heap = GetNwAllocatorHeap();
    Show();
    mClearColor = CapturePane::setupClearColor_(heap, this, layout, &mCaptureFlags);
    const auto* data = FindExtUserDataByName("DynamicCaptureOn");
    if (data && sead::SafeString(data->GetString()) == "R10G10B10A2")
        mCaptureFlags.setBit(2);
    CapturePane::setupCaptureOutputAlpha255_(this, &mCaptureFlags);
    CapturePane::setupCaptureOriginalSize_(this, &mCaptureFlags);
    mMultiFilter = InitializeMultiFilter(heap, *this, layout);
    if (mMultiFilter)
        mMultiFilter->setUseTextureAlpha(true);
    mRenderBuffer.mRenderTargetColor[0] = &mRenderTarget;
    std::memcpy(&mMtx, &sead::Matrix34f::ident, sizeof(mMtx));
    SetUserGlobalMatrix(true);
}

DynamicCapturePane::~DynamicCapturePane() {
    if (mClearColor) {
        delete mClearColor;
        mClearColor = nullptr;
    }
}

// 0x7100bf2e30
// NON_MATCHING: projection argument scheduling differs and the device matrix copy uses memcpy.
void DynamicCapturePane::Calculate(nn::ui2d::DrawInfo& info,
                                   nn::ui2d::Pane::CalculateContext& context, bool b) {
    if (!IsVisible() || GetAlpha() == 0)
        return;
    const bool saved = context._1f;
    context._1f = false;
    nn::util::Matrix4x4fType proj_mtx = info.mProjMtx;
    {
        const auto& size = GetSize();
        sead::OrthoProjection projection(0.0f, 300.0f, size.height * 0.5f, size.height * -0.5f,
                                        size.width * -0.5f, size.width * 0.5f);
        nn::util::Matrix4x4fType matrix;
        std::memcpy(&matrix, &projection.getDeviceProjectionMatrix(), sizeof(matrix));
        info.SetProjMtx(matrix);
        nn::ui2d::Pane::Calculate(info, context, b);
        info.SetProjMtx(proj_mtx);
    }
    context._1f = saved;
}

// NON_MATCHING: framebuffer/texture copies and temporary lifetimes differ,
// with different stack slots and branch scheduling.
// 0x7100bf2f18
void DynamicCapturePane::Draw(nn::ui2d::DrawInfo& info, nn::gfx::CommandBuffer& command_buffer) {
    auto& draw_info = static_cast<DrawInfoEx&>(info);
    if (draw_info._100 || !IsVisible() || GetAlpha() == 0 || !draw_info._f8)
        return;
    const auto* render_info = draw_info._f8;
    mTexture = sub_7100BF2530(this, info, &mCaptureFlags, mMultiFilter, &mRenderBuffer,
                            &mRenderTarget, mClearColor, command_buffer);
    if (const auto* scale_data = FindExtUserDataByName("CaptureScale")) {
        const f32 scale = scale_data->GetFloatArray()[0];
        const f32 width = scale * GetSize().width;
        const f32 height = scale * GetSize().height;
        auto* resized = agl::utl::DynamicTextureAllocator::instance()->alloc(
            render_info->mDrawContext, mTexture->getDebugLabel(), mTexture->getFormat(),
            u32(width), u32(height), 1, nullptr,
            static_cast<agl::utl::DynamicTextureAllocator::AllocateType>(0), true, false);
        mRenderTarget.applyTextureData(*resized, mRenderTarget.getMipLevel(), mRenderTarget.getLayer());
        mRenderBuffer.setVirtualSize({width, height});
        mRenderBuffer.setPhysicalArea(0.0f, 0.0f, width, height);
        mRenderBuffer.bind(render_info->mDrawContext);
        sead::GraphicsContext context;
        // BF3100 clears blend bit0; BF3104 clears only depth-test byte0.
        context.setBlendEnable(false, 0);
        context.setDepthTestEnable(false);
        context.apply(render_info->mDrawContext);
        agl::TextureSampler sampler(*mTexture);
        sead::Viewport viewport(mRenderBuffer);
        viewport.apply(render_info->mDrawContext, mRenderBuffer);
        agl::utl::ImageFilter2D::drawTextureQuadTriangle(render_info->mDrawContext, sampler);
        mRenderTarget.invalidateGPUCache(render_info->mDrawContext);
        if (mMultiFilter && mMultiFilter->getResultTexture())
            mMultiFilter->freeResultTexture();
        else
            agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
        mTexture = resized;
    }
    if (mCaptureFlags.isOnBit(3)) {
        mTexture->setCompSel(mTexture->getCompSelRed(), mTexture->getCompSelGreen(),
                            mTexture->getCompSelBlue(), agl::TextureCompSel::cTextureCompSel_One);
    }
    SetupTextureInfoByAglTextureData(&mTextureInfo, *mTexture, nullptr);
    draw_info.mDynamicTextures.push_back(*this);
    DrawInfoEx::applyRenderBufferInfo(render_info);
    info._eb[4] = 1;
}

// 0x7100bf3214
void DynamicCapturePane::freeDynamicTexture() {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
    mTexture = nullptr;
}

}  // namespace eui
