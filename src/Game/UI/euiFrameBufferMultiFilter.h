#pragma once

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <utility/aglMultiFilter.h>
#include "KingSystem/Utils/Types.h"

namespace eui {

class FrameBufferMultiFilter {
public:
    FrameBufferMultiFilter();
    virtual ~FrameBufferMultiFilter();
    void freeResultTexture(const agl::TextureData* texture);

private:
    /* 0x08 */ agl::utl::MultiFilter* mMultiFilter = nullptr;
    /* 0x10 */ agl::RenderBuffer mRenderBuffer;
    /* 0x78 */ agl::RenderTargetColor mRenderTarget;
    /* 0x1f0 */ u16 _1f0 = 0;
    /* 0x1f2 */ u16 _1f2 = 0;
    /* 0x1f4 */ u16 _1f4 = 5;
    /* 0x1f6 */ s8 mTextureIndex = -1;
};
KSYS_CHECK_SIZE_NX150(FrameBufferMultiFilter, 0x1f8);

}  // namespace eui
