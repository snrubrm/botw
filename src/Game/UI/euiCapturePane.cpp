#include "Game/UI/euiCapturePane.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiFrameBufferMultiFilter.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"

#include <cstring>
#include <gfx/seadProjection.h>
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
