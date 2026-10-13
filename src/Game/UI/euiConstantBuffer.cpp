#include "Game/UI/euiConstantBuffer.h"
#include <nn/ui2d/DrawInfo.h>
#include "Game/gameUnkRttiPlaceholders.h"

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

// NON_MATCHING: placeholder destructor; the original (0x7100c0f90c) also destroys members or bases
// this class does not declare yet.
Unk_71024ca688::~Unk_71024ca688() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100c66fb8) also destroys members or bases
// this class does not declare yet.
Unk_71024cffe8::~Unk_71024cffe8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100c7fcb8) also destroys members or bases
// this class does not declare yet.
Unk_71024d1af8::~Unk_71024d1af8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100f2b358) also destroys members or bases
// this class does not declare yet.
Unk_71024f4720::~Unk_71024f4720() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100c07e74) also destroys members or bases
// this class does not declare yet.
Unk_7102531f60::~Unk_7102531f60() = default;
