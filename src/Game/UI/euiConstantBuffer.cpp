#include "Game/UI/euiConstantBuffer.h"

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

}  // namespace eui
