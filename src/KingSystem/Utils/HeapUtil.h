#pragma once

#include <basis/seadTypes.h>
#include <heap/seadExpHeap.h>
#include <heap/seadFrameHeap.h>
#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class DualHeap final : public sead::ExpHeap {
    SEAD_RTTI_OVERRIDE(DualHeap, sead::ExpHeap)

public:
    static DualHeap* tryCreate(size_t size, const sead::SafeString& name, Heap* parent1,
                               Heap* parent2, s32 alignment, HeapDirection direction, bool b);
    static DualHeap* create(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2,
                            s32 alignment, HeapDirection direction, bool b);

    void* tryAlloc(size_t size, s32 alignment, bool* ok);

    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    void* resizeFront(void* p_void, size_t size) override;
    void* resizeBack(void* p_void, size_t size) override;
    void* tryRealloc(void* ptr, size_t size, s32 alignment) override;
    void freeAll() override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isResizable() const override;
    bool isAdjustable() const override;
    void dumpYAML(sead::WriteStream& stream, int i) const override;
    void genInformation_(sead::hostio::Context* context) override;
    void makeMetaString_(sead::BufferedSafeString* string) override;

    // Native 12B184C and independent 11AB294 / FC9F40 query only the primary heap.
    size_t sub_71010BF054() const;
    size_t sub_71010BF058(s32 alignment) const;

    sead::Heap* getHeap2() const { return mHeap2; }

protected:
    DualHeap(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2, s32 alignment,
             HeapDirection direction, bool b);
    ~DualHeap() override;

    sead::Heap* mHeap2;
    // Complete tryCreate 10BEC7C and tryAlloc 10BF05C count fallback-request bytes.
    size_t _118;
    u8 _120;
    void* _128;
};
KSYS_CHECK_SIZE_NX150(sead::ExpHeap, 0x110);
KSYS_CHECK_SIZE_NX150(DualHeap, 0x130);

class DualFrameHeap final : public sead::FrameHeap {
    SEAD_RTTI_OVERRIDE(DualFrameHeap, sead::FrameHeap)

public:
    static DualFrameHeap* tryCreate(size_t size, const sead::SafeString& name, Heap* parent1,
                                    Heap* parent2, s32 alignment, HeapDirection direction, bool b);
    static DualFrameHeap* create(size_t size, const sead::SafeString& name, Heap* parent1,
                                 Heap* parent2, s32 alignment, HeapDirection direction, bool b);

    size_t adjust() override;
    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    void freeAll() override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isInclude(const void* p_void) const override;
    bool isEmpty() const override;
    bool isAdjustable() const override;
    void genInformation_(sead::hostio::Context* context) override;
    void makeMetaString_(sead::BufferedSafeString* string) override;
    void dumpYAML(sead::WriteStream& stream, int i) const override;

    sead::Heap* getHeap2() const { return mHeap2; }

protected:
    DualFrameHeap(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2,
                  s32 alignment, HeapDirection direction, bool b);
    ~DualFrameHeap() override;

    // Same usable-area sequence in complete 10BDD10, 10BE3F8, 10BE3C0 and 10BE5A8.
    void* getAreaStart_() const;
    void* getAreaEnd_() const;

    sead::Heap* mHeap2;
    // Complete producer 10BDD10 and both fallback allocation paths count requested bytes.
    size_t _f8;
    u8 _100;
};
KSYS_CHECK_SIZE_NX150(sead::FrameHeap, 0xf0);
KSYS_CHECK_SIZE_NX150(DualFrameHeap, 0x108);

// Complete producer 10BDD10 takes six arguments and constructs a DualFrameHeap.
DualFrameHeap* sub_71010BDD10(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                              sead::Heap* heap2, sead::Heap::HeapDirection direction, bool b);

sead::Heap* tryCreateDualHeap(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                              sead::Heap* heap2, sead::Heap::HeapDirection direction, bool b);

/// Creates a dual heap that is as large as possible.
sead::Heap* tryCreateDualHeap(sead::Heap* parent);

/// Same as tryCreateDualHeap, but asserts on failure.
sead::Heap* createDualHeap(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                           sead::Heap* heap2, sead::Heap::HeapDirection direction, bool b);

/// Returns the specified heap if it is not null. Otherwise, this returns the current heap.
sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap);

void adjustHeapOrCurrentHeap(sead::Heap* heap);

sead::Heap* getCurrentHeap();
sead::Heap* getDebugHeap();
sead::Heap* getDebugHeap2();

KSYS_ALWAYS_INLINE inline sead::Heap* tryCreateDualHeap(sead::Heap* parent) {
    size_t size;

    if (const auto* parent_ex = sead::DynamicCast<DualHeap>(parent)) {
        if (parent_ex->sub_71010BF058(sizeof(void*)) < sizeof(DualFrameHeap))
            size = sizeof(DualFrameHeap);
        else
            size = parent_ex->sub_71010BF058(sizeof(void*));

        return sub_71010BDD10(size, parent->getName(), parent, parent_ex->getHeap2(),
                                 sead::Heap::cHeapDirection_Forward, false);
    }

    if (parent->getMaxAllocatableSize(sizeof(void*)) < sizeof(DualFrameHeap))
        size = sizeof(DualFrameHeap);
    else
        size = parent->getMaxAllocatableSize(sizeof(void*));

    return sub_71010BDD10(size, parent->getName(), parent, getDebugHeap(),
                             sead::Heap::cHeapDirection_Forward, false);
}

/// Allocate uninitialised, suitably aligned storage for an object of type T.
template <typename T>
inline void* allocStorage(sead::Heap* heap, size_t alignment = alignof(T)) {
    return heap->alloc(sizeof(T), static_cast<int>(alignment));
}

template <typename T, typename... Args>
inline T* alloc(sead::Heap* heap, Args&&... args) {
    void* storage = allocStorage<T>(heap);
    return new (storage) T(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline T* allocWithAlign(sead::Heap* heap, size_t alignment, Args&&... args) {
    void* storage = allocStorage<T>(heap, alignment);
    return new (storage) T(std::forward<Args>(args)...);
}

}  // namespace ksys::util
