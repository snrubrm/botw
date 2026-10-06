#include "Game/UI/euiConstantBuffer.h"
#include <nn/ui2d/DrawInfo.h>

namespace eui {

// 0x7100bf42f8
void ConstantBuffer::map() {
    if (_1a9) {
        mGpuBuffers[0].Unmap();
        mGpuBuffers[0].SetBufferIndex(mIndex);
        mGpuBuffers[0].Map(mIndex);
    }
    if (_1aa) {
        mGpuBuffers[1].Unmap();
        mGpuBuffers[1].SetBufferIndex(mIndex);
        mGpuBuffers[1].Map(mIndex);
    }
}

// 0x7100bf4364
void ConstantBuffer::unmap() {}

// 0x7100bf4368
void ConstantBuffer::applyToDrawInfo(nn::ui2d::DrawInfo* draw_info) {
    draw_info->mUi2dConstantBuffer = &mGpuBuffers[0];
    draw_info->mFontConstantBuffer = &mGpuBuffers[1];
}

}  // namespace eui
