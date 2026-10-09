#include "Game/UI/euiCapturePane.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiTypes.h"

#include <cstring>
#include <gfx/seadProjection.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadViewport.h>
#include <common/aglDrawContext.h>
#include <common/aglTextureSampler.h>
#include <common/aglTextureFormatInfo.h>
#include <utility/aglImageFilter2D.h>
#include <utility/aglMultiFilter.h>
#include <nn/ui2d/BuildTypes.h>
#include <nn/ui2d/DrawInfo.h>
#include <nn/ui2d/Pane.h>
#include <heap/seadHeap.h>
#include <nn/ui2d/ResExtUserData.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace eui {

CapturePane::CapturePane(const nn::ui2d::ResPane* resource, const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Pane(resource, args) {
    initialize_(const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

CapturePane::CapturePane(const CapturePane& other, LayoutEx* layout)
    : nn::ui2d::Pane(other), _dc(other._dc) {
    initialize_(layout);
}

// 0x7100bf1348
void CapturePane::initialize_(LayoutEx* layout) {
    auto* heap = GetNwAllocatorHeap();
    Show();
    mClearColor = setupClearColor_(heap, this, layout, &mCaptureFlags);
    if (FindExtUserDataByName("CaptureWorkFormat"))
        mCaptureFlags.setBit(2);
    setupCaptureOutputAlpha255_(this, &mCaptureFlags);
    setupCaptureOriginalSize_(this, &mCaptureFlags);
    mMultiFilter = InitializeMultiFilter(heap, *this, layout);
    if (mMultiFilter)
        mMultiFilter->setUseTextureAlpha(true);
    mRenderBuffer.mRenderTargetColor[0] = &mRenderTarget;
    std::memcpy(&mMtx, &sead::Matrix34f::ident, sizeof(mMtx));
    SetUserGlobalMatrix(true);
    if (layout->mScreen)
        layout->mScreen->_107 |= 0x10;
}

CapturePane::~CapturePane() {
    if (mClearColor) {
        delete mClearColor;
        mClearColor = nullptr;
    }
    sub_7100BF1E64();
}

// NON_MATCHING: the projection matrix copy is a memcpy call here (the original copies it in q registers; same as
// SetupDrawInfoOrtho), and the flag bit 5 update is a select instead of two branches.
// 0x7100bf1f7c
void CapturePane::Calculate(nn::ui2d::DrawInfo& info, nn::ui2d::Pane::CalculateContext& context, bool b) {
    if (!_db && !_dc)
        return;
    if (!IsVisible() || GetAlpha() == 0)
        return;

    _dd = true;
    const bool saved = context._1f;
    context._1f = false;
    context._28 = false;
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
    if (context._28)
        mCaptureFlags.setBit(5);
    else
        mCaptureFlags.resetBit(5);
}

// NON_MATCHING: texture copy/destruction calls, framebuffer copies, graphics-state stores and branch scheduling differ.
// 0x7100bf20a0
void CapturePane::Draw(nn::ui2d::DrawInfo& info, nn::gfx::CommandBuffer& command_buffer) {
    auto& draw_info = static_cast<DrawInfoEx&>(info);
    if (!_dd || draw_info._100 || !draw_info._f8)
        return;
    const auto* render_info = draw_info._f8;
    const auto* work = sub_7100BF2530(this, info, &mCaptureFlags, mMultiFilter, &mRenderBuffer,
                                     &mRenderTarget, mClearColor, command_buffer);
    const auto format = mTexture->getFormat();
    const auto alpha = mTexture->getCompSelAlpha();
    if (agl::TextureFormatInfo::sub_7100B3B86C(format)) {
        if (((format == agl::TextureFormat::cTextureFormat_R8_uNorm ||
              format == agl::TextureFormat::cTextureFormat_BC4_uNorm) &&
             alpha == agl::TextureCompSel::cTextureCompSel_Red) ||
            format == agl::TextureFormat::cTextureFormat_R8_G8_uNorm ||
            format == agl::TextureFormat::cTextureFormat_BC5_uNorm) {
            agl::TextureData copy(*work);
            copy.setCompSel(alpha == agl::TextureCompSel::cTextureCompSel_Red ?
                                agl::TextureCompSel::cTextureCompSel_Alpha :
                                agl::TextureCompSel::cTextureCompSel_Red,
                            alpha == agl::TextureCompSel::cTextureCompSel_Red ?
                                agl::TextureCompSel::cTextureCompSel_One :
                                agl::TextureCompSel::cTextureCompSel_Alpha,
                            agl::TextureCompSel::cTextureCompSel_One,
                            agl::TextureCompSel::cTextureCompSel_One);
            copy.sub_7100B39774(render_info->mDrawContext, mTexture, 0, 0);
        } else {
            work->sub_7100B39774(render_info->mDrawContext, mTexture, 0, 0);
        }
    } else {
        const u32 width = sead::Mathu::max(mTexture->getWidth(), 1u);
        const u32 height = sead::Mathu::max(mTexture->getHeight(), mTexture->getMinHeight_());
        mRenderTarget.applyTextureData(*mTexture, mRenderTarget.getMipLevel(), mRenderTarget.getLayer());
        mRenderBuffer.setVirtualSize({f32(width), f32(height)});
        mRenderBuffer.setPhysicalArea(0.0f, 0.0f, width, height);
        mRenderBuffer.bind(render_info->mDrawContext);
        sead::GraphicsContext context;
        context.setDepthTestEnable(false);
        context.setDepthWriteEnable(false);
        context.setStencilTestEnable(false);
        context.setBlendEnable(false, 0);
        context.apply(render_info->mDrawContext);
        agl::TextureSampler sampler(*work);
        if ((format == agl::TextureFormat::cTextureFormat_R8_uNorm ||
             format == agl::TextureFormat::cTextureFormat_BC4_uNorm) &&
            alpha == agl::TextureCompSel::cTextureCompSel_Red) {
            sampler.setCompSel(agl::TextureCompSel::cTextureCompSel_Alpha,
                               agl::TextureCompSel::cTextureCompSel_One,
                               agl::TextureCompSel::cTextureCompSel_One,
                               agl::TextureCompSel::cTextureCompSel_One);
        } else if (format == agl::TextureFormat::cTextureFormat_R8_G8_uNorm ||
                   format == agl::TextureFormat::cTextureFormat_BC5_uNorm) {
            sampler.setCompSel(agl::TextureCompSel::cTextureCompSel_Red,
                               agl::TextureCompSel::cTextureCompSel_Alpha,
                               agl::TextureCompSel::cTextureCompSel_One,
                               agl::TextureCompSel::cTextureCompSel_One);
        }
        if (sead::Mathu::max(work->getWidth(), 1u) != sead::Mathu::max(mTexture->getWidth(), 1u) ||
            sead::Mathu::max(work->getHeight(), work->getMinHeight_()) !=
                sead::Mathu::max(mTexture->getHeight(), mTexture->getMinHeight_())) {
            sead::Viewport viewport(mRenderBuffer);
            viewport.apply(render_info->mDrawContext, mRenderBuffer);
        }
        agl::utl::ImageFilter2D::drawTextureQuadTriangle(render_info->mDrawContext, sampler);
    }
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(work);
    mRenderTarget.invalidateGPUCache(render_info->mDrawContext);
    DrawInfoEx::applyRenderBufferInfo(render_info);
    info._eb[4] = 1;
    mCaptureFlags.setBit(0);
    _db = mCaptureFlags.isOnBit(5);
    _dd = false;
}

// NON_MATCHING: the allocator name SafeString temporary occupies a different stack slot.
// 0x7100bf166c
void CapturePane::initializeCaptureTextureData_(const char* layout_name) {
    if (mTexture)
        return;
    const sead::SafeString type(FindExtUserDataByName("CaptureOn")->GetString());
    auto format = agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm;
    bool alpha_only = false;
    if (type == "RGBA8") {
        format = agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm;
    } else if (type == "BC3") {
        format = agl::TextureFormat::cTextureFormat_BC3_uNorm;
    } else if (type == "BC1") {
        format = agl::TextureFormat::cTextureFormat_BC1_uNorm;
    } else if (type == "RGB565") {
        // Native bf1908 selects RGBA8 for this resource value too.
        format = agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm;
    } else if (type == "R10G10B10A2") {
        format = agl::TextureFormat::cTextureFormat_R10_G10_B10_A2_uNorm;
    } else if (type == "L8") {
        format = agl::TextureFormat::cTextureFormat_R8_uNorm;
    } else if (type == "A8") {
        format = agl::TextureFormat::cTextureFormat_R8_uNorm;
        alpha_only = true;
    } else if (type == "LA8") {
        format = agl::TextureFormat::cTextureFormat_R8_G8_uNorm;
    } else if (type == "BC4L") {
        format = agl::TextureFormat::cTextureFormat_BC4_uNorm;
    } else if (type == "BC4A") {
        format = agl::TextureFormat::cTextureFormat_BC4_uNorm;
        alpha_only = true;
    } else if (type == "BC5") {
        format = agl::TextureFormat::cTextureFormat_BC5_uNorm;
    }
    f32 width = GetSize().width;
    f32 height = GetSize().height;
    if (const auto* data = FindExtUserDataByName("CaptureScale")) {
        const f32 scale = data->GetFloatArray()[0];
        if (scale > 0.0f && scale < 1.0f) {
            width *= scale;
            height *= scale;
        }
    }
    mTexture = agl::utl::DynamicTextureAllocator::instance()->sub_7100B46FC8(
        nullptr, layout_name, format, sead::Mathf::round(width), sead::Mathf::round(height), 1,
        nullptr, static_cast<agl::utl::DynamicTextureAllocator::AllocateType>(1), true, false);
    auto red = mTexture->getCompSelRed();
    auto green = mTexture->getCompSelGreen();
    auto blue = mTexture->getCompSelBlue();
    auto alpha = mTexture->getCompSelAlpha();
    if (format == agl::TextureFormat::cTextureFormat_R8_uNorm ||
        format == agl::TextureFormat::cTextureFormat_BC4_uNorm) {
        red = alpha_only ? agl::TextureCompSel::cTextureCompSel_One :
                           agl::TextureCompSel::cTextureCompSel_Red;
        green = red;
        blue = red;
        alpha = alpha_only ? agl::TextureCompSel::cTextureCompSel_Red :
                             agl::TextureCompSel::cTextureCompSel_One;
    } else if (format == agl::TextureFormat::cTextureFormat_R8_G8_uNorm ||
               format == agl::TextureFormat::cTextureFormat_BC5_uNorm) {
        red = agl::TextureCompSel::cTextureCompSel_Red;
        green = red;
        blue = red;
        alpha = agl::TextureCompSel::cTextureCompSel_Green;
    }
    if (mCaptureFlags.isOnBit(3))
        alpha = agl::TextureCompSel::cTextureCompSel_One;
    mTexture->setCompSel(red, green, blue, alpha);
    SetupTextureInfoByAglTextureData(&mTextureInfo, *mTexture, nullptr);
    _db = true;
}

// 0x7100bf1e64
void CapturePane::sub_7100BF1E64() {
    if (mTexture) {
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
        mTexture = nullptr;
    }
}

// NON_MATCHING: byte-to-float conversion and color-store scheduling differ.
// 0x7100bf14f0
sead::Color4f* CapturePane::setupClearColor_(sead::Heap* heap, nn::ui2d::Pane* pane,
                                           LayoutEx*, sead::BitFlag<u8>* flags) {
    const auto* rgb = pane->FindExtUserDataByName("CaptureBGColor");
    const auto* alpha = pane->FindExtUserDataByName("CaptureBGAlpha");
    if (rgb && rgb->GetCount() == 3) {
        const auto* values = rgb->GetIntArray();
        auto* color = new (heap, 8) sead::Color4f;
        color->r = static_cast<u8>(values[0]) / 255.0f;
        color->g = static_cast<u8>(values[1]) / 255.0f;
        color->b = static_cast<u8>(values[2]) / 255.0f;
        color->a = 0.0f;
        if (alpha)
            color->a = alpha->GetIntArray()[0] / 255.0f;
        return color;
    }
    if (alpha && alpha->GetIntArray()[0] == 255)
        flags->setBit(1);
    return nullptr;
}

// 0x7100bf15ec
void CapturePane::setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags) {
    const auto* data = pane->FindExtUserDataByName("CaptureOutputAlpha");
    if (data && data->GetIntArray()[0] == 255)
        flags->setBit(3);
}

// 0x7100bf1634
void CapturePane::setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags) {
    if (pane->FindExtUserDataByName("CaptureOriginalSize"))
        flags->setBit(4);
}

}  // namespace eui
