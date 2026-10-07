#include "Game/UI/euiFrameBufferMultiFilter.h"
#include <utility/aglDynamicTextureAllocator.h>
#include <nn/ui2d/Material.h>
#include "Game/UI/euiWindowEx.h"
#include "Game/UI/euiTypes.h"

namespace eui {

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
