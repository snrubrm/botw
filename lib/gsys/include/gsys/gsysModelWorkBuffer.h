#pragma once

#include <common/aglGPUMemAddr.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>

namespace sead {
class Heap;
class WorkerMgr;
}  // namespace sead

namespace gsys {

// Per-core work buffers (0x188 bytes, createInstance 0x7100c6b210). The disposer calls the
// destructor through slot 1, so the class has a hostio::Node base.
class ModelWorkBuffer : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ModelWorkBuffer)
public:
    // One display-list buffer of the double-buffered pair (start and write position).
    struct DisplayList {
        u8* mStart;
        u8* mCurrent;
    };

    // One core's share (0x58 bytes, stride from getBufferPtr / getFreeSize).
    struct CoreBuffer {
        u8* mStart;
        u8* mCurrent;
        u32 mSize;
        u32 mMinFreeSize;
        agl::GPUMemAddrBase mDisplayListAddr;
        DisplayList mDisplayLists[2];
        u32 mDisplayListSize;
        u32 mDisplayListMinFreeSize;
    };
    static_assert(sizeof(CoreBuffer) == 0x58);

    ModelWorkBuffer() = default;
    virtual ~ModelWorkBuffer();

    void initialize(u32 num_display_list, void* buffer, u32 size, sead::Heap* heap,
                    sead::Heap* debug_heap);
    void clear(sead::WorkerMgr* worker_mgr);
    void roundUpBuffer(s32 core, u32 size);
    u8** getBufferPtr(s32 core);
    agl::GPUMemVoidAddr lockAndBeginUseDisplayListBuffer();
    void unlockAndEndUseDisplayListBuffer();
    u32 getFreeSize(s32 core) const;

private:
    void* mBuffer = nullptr;
    u32 mBufferSize = 0;
    CoreBuffer mCoreBuffers[3];
    u8 mDisplayListIndex;
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(ModelWorkBuffer) == 0x188);

}  // namespace gsys
