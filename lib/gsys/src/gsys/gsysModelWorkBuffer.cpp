#include "gsys/gsysModelWorkBuffer.h"
#include <common/aglGPUMemBlock.h>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include "gsys/gsysORUtil.h"

namespace gsys {

SEAD_SINGLETON_DISPOSER_IMPL(ModelWorkBuffer)

ModelWorkBuffer::~ModelWorkBuffer() {
    mBuffer = nullptr;
    for (s32 i = 0; i < 3; ++i) {
        CoreBuffer& buffer = mCoreBuffers[i];
        buffer.mDisplayListAddr.deleteGPUMemBlock();
        for (s32 j = 0; j < 2; ++j) {
            if (buffer.mDisplayLists[j].mStart) {
                // The original frees these with scalar delete although they come from new[].
                delete buffer.mDisplayLists[j].mStart;
                buffer.mDisplayLists[j].mStart = nullptr;
            }
        }
    }
}

// NON_MATCHING: the original keeps the allocating per-core loop rolled (ours is unrolled).
void ModelWorkBuffer::initialize(u32 num_display_list, void* buffer, u32 size, sead::Heap* heap,
                                 sead::Heap* debug_heap) {
    mBufferSize = size;
    mBuffer = buffer;
    const u32 display_list_size = num_display_list << 8;
    if (display_list_size != 0) {
        for (s32 i = 0; i < 3; ++i) {
            CoreBuffer& core = mCoreBuffers[i];
            auto* block = new (heap) agl::GPUMemBlock<u8>;
            block->allocBuffer_(0x800, heap, 0x40, agl::MemoryAttribute::_00);
            core.mDisplayListAddr = agl::GPUMemAddrBase(*block, 0);
            core.mDisplayListAddr.invalidateCPUCache(0x800);
            core.mMinFreeSize = mBufferSize;
            core.mDisplayListSize = display_list_size;
            core.mDisplayLists[0].mStart = core.mDisplayLists[0].mCurrent =
                new (heap, 0x100) u8[display_list_size];
            core.mDisplayLists[1].mStart = core.mDisplayLists[1].mCurrent =
                new (heap, 0x100) u8[core.mDisplayListSize];
        }
    } else {
        for (s32 i = 0; i < 3; ++i) {
            CoreBuffer& core = mCoreBuffers[i];
            auto* block = new (heap) agl::GPUMemBlock<u8>;
            block->allocBuffer_(0x800, heap, 0x40, agl::MemoryAttribute::_00);
            core.mDisplayListAddr = agl::GPUMemAddrBase(*block, 0);
            core.mDisplayListAddr.invalidateCPUCache(0x800);
            core.mMinFreeSize = mBufferSize;
            core.mDisplayListSize = 0;
            core.mDisplayLists[0].mStart = core.mDisplayLists[0].mCurrent = nullptr;
            core.mDisplayLists[1].mStart = core.mDisplayLists[1].mCurrent = nullptr;
        }
    }

    mDisplayListIndex = 1;
    for (s32 i = 0; i < 3; ++i) {
        CoreBuffer& core = mCoreBuffers[i];
        core.mStart = core.mCurrent = static_cast<u8*>(mBuffer);
        core.mSize = mBufferSize;
        DisplayList& list = core.mDisplayLists[mDisplayListIndex];
        list.mCurrent = list.mStart;
    }
    ORUtil::setNodeMeta(this, ORUtil::Category::_1, ORUtil::Attribute::_2, debug_heap);
}

// NON_MATCHING: the original divides with a 64-bit multiply and allocates registers differently.
void ModelWorkBuffer::clear(sead::WorkerMgr* worker_mgr) {
    const u32 buffer_size = mBufferSize;
    mDisplayListIndex = 1 - mDisplayListIndex;
    if (worker_mgr) {
        const u32 size = (buffer_size / 3) & ~0x3fu;
        for (s32 i = 0; i < 3; ++i) {
            CoreBuffer& core = mCoreBuffers[i];
            core.mStart = core.mCurrent = static_cast<u8*>(mBuffer) + size * i;
            core.mSize = size;
            DisplayList& list = core.mDisplayLists[mDisplayListIndex];
            list.mCurrent = list.mStart;
        }
    } else {
        for (s32 i = 0; i < 3; ++i) {
            CoreBuffer& core = mCoreBuffers[i];
            core.mStart = core.mCurrent = static_cast<u8*>(mBuffer);
            core.mSize = buffer_size;
            DisplayList& list = core.mDisplayLists[mDisplayListIndex];
            list.mCurrent = list.mStart;
        }
    }
}

void ModelWorkBuffer::roundUpBuffer(s32 core, u32 size) {
    CoreBuffer& buffer = mCoreBuffers[core];
    buffer.mCurrent = reinterpret_cast<u8*>((uintptr_t(buffer.mCurrent) + 0x1f) & ~uintptr_t(0x1f));

    const s32 current = sead::CoreInfo::getCurrentCoreId();
    CoreBuffer& stats = mCoreBuffers[current];
    const u32 free_size = stats.mSize - u32(stats.mCurrent - stats.mStart);
    if (free_size < stats.mMinFreeSize)
        stats.mMinFreeSize = free_size;
    const DisplayList& list = stats.mDisplayLists[mDisplayListIndex];
    if (free_size < stats.mDisplayListMinFreeSize) {
        stats.mDisplayListMinFreeSize = stats.mDisplayListSize - u32(list.mCurrent - list.mStart);
    }
}

u8** ModelWorkBuffer::getBufferPtr(s32 core) {
    return &mCoreBuffers[core].mCurrent;
}

agl::GPUMemVoidAddr ModelWorkBuffer::lockAndBeginUseDisplayListBuffer() {
    mCriticalSection.lock();
    return mCoreBuffers[sead::CoreInfo::getCurrentCoreId()].mDisplayListAddr;
}

void ModelWorkBuffer::unlockAndEndUseDisplayListBuffer() {
    mCriticalSection.unlock();
}

u32 ModelWorkBuffer::getFreeSize(s32 core) const {
    const CoreBuffer& buffer = mCoreBuffers[core];
    return buffer.mSize - u32(buffer.mCurrent - buffer.mStart);
}

}  // namespace gsys
