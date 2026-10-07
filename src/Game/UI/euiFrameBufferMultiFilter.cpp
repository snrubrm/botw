#include "Game/UI/euiFrameBufferMultiFilter.h"
#include <utility/aglDynamicTextureAllocator.h>
#include <nn/ui2d/Material.h>
#include <nn/ui2d/ResExtUserData.h>
#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiWindowEx.h"
#include "Game/UI/euiTypes.h"

namespace eui {

// NON_MATCHING: the compiler shares the alpha-mode stores and lays out their branches differently.
void FrameBufferMultiFilter::initialize(sead::Heap* heap, const nn::ui2d::Pane& pane,
                                      LayoutEx* layout) {
    const auto* data = pane.FindExtUserDataByName("FrameBufferUse");
    const auto* values = data->GetIntArray();
    const u16 value_count = data->GetCount();
    const s32 texture_index = values[0];
    // Original virtual calls stay through the pointer (approved pointer form).
    const auto* pane_ptr = &pane;
    const u8 material_count = pane_ptr->GetMaterialCount();
    s32 texture_count = 0;
    for (s32 i = 0; i < material_count; ++i)
        texture_count = sead::Mathi::max(pane_ptr->GetMaterial(i)->GetTexMapCount(), texture_count);
    if (texture_index >= 0 && texture_index < texture_count) {
        mTextureIndex = texture_index;
        _1f0 = value_count > 1 ? values[1] * 2 : 0;
        _1f2 = value_count > 2 ? values[2] * 2 : 0;
        mMultiFilter = InitializeMultiFilter(heap, pane, layout);
    }
    mRenderBuffer.mRenderTargetColor[0] = &mRenderTarget;
    if (const auto* alpha = pane.FindExtUserDataByName("FrameBufferAlpha")) {
        const s32 value = alpha->GetIntArray()[0];
        if (value == 255)
            _1f4 = 1;
        else if (value == 0)
            _1f4 = 0;
    }
}

FrameBufferMultiFilter::FrameBufferMultiFilter() = default;

FrameBufferMultiFilter::~FrameBufferMultiFilter() = default;

void FrameBufferMultiFilter::freeResultTexture(const agl::TextureData* texture) {
    if (mMultiFilter && mMultiFilter->getResultTexture())
        mMultiFilter->freeResultTexture();
    else
        agl::utl::DynamicTextureAllocator::instance()->free(texture);
}

void FrameBufferMultiFilter::applyTextureDataToWindowMaterial(
    WindowEx* window, nn::ui2d::TextureInfo* info, const agl::TextureData* texture,
    const DrawInfoEx& draw_info) {
    SetupTextureInfoByAglTextureData(info, *texture, nullptr);
    // Original virtual calls stay through the pointer (approved pointer form).
    const u8 count = window->GetMaterialCount();
    for (s32 i = 0; i < count; ++i) {
        auto* material = window->GetMaterial(i);
        if (mTextureIndex < material->GetTexMapCount())
            material->GetTexMapArray()[mTextureIndex].ReplaceTextureInfo(info);
    }
}

}  // namespace eui
