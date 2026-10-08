#include "Game/UI/euiDynamicCapturePane.h"
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

// 0x7100bf3214
void DynamicCapturePane::freeDynamicTexture() {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(mTexture);
    mTexture = nullptr;
}

}  // namespace eui
