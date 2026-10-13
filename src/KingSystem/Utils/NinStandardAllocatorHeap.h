#pragma once

#include <heap/seadHeap.h>
#include <nn/mem.h>
#include "KingSystem/Utils/Types.h"

// Named native heap table 25198E0; complete producer 12A4770 constructs the allocator
// at +E0 and initializes its storage immediately after this 0x128 owner.
class NinStandardAllocatorHeap : public sead::Heap {
    // NON_MATCHING: native RTTI addresses the owner-local statics directly; this form uses the GOT.
    SEAD_RTTI_OVERRIDE(NinStandardAllocatorHeap, sead::Heap)
public:
    ~NinStandardAllocatorHeap() override;
    void destroy() override;
    size_t adjust() override;
    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    void* resizeFront(void* ptr, size_t size) override;
    void* resizeBack(void* ptr, size_t size) override;
    void* tryRealloc(void* ptr, size_t size, s32 alignment) override;
    void freeAll() override;
    uintptr_t getStartAddress() const override;
    uintptr_t getEndAddress() const override;
    size_t getSize() const override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isInclude(const void* ptr) const override;
    bool isEmpty() const override;
    bool isFreeable() const override;
    bool isResizable() const override;
    bool isAdjustable() const override;
    void dump() const override;
    void dumpYAML(sead::WriteStream& stream, int indent) const override;
    void genInformation_(sead::hostio::Context* context) override;

private:
    nn::mem::StandardAllocator mAllocator;
};
KSYS_CHECK_SIZE_NX150(NinStandardAllocatorHeap, 0x128);

