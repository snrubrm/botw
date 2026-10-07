#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

// TODO: very incomplete
class CompactedHeap {
public:
    CompactedHeap(const sead::SafeString& name, void* buffer, size_t buffer_size, u32 x);
    static CompactedHeap* create(const sead::SafeString& name, void* buffer, size_t buffer_size,
                                 u32 x);

    void destroy();
    void incrementCompactionCount();
    bool setBuffer(void* buffer, size_t size);
    bool compact();

    // 0x71012b5900 (CSV CompactedHeap::x; declared only)
    void x(const sead::SafeString& name, bool b);
    // The state (_5c90): 3 once the compaction is finished.
    s32 getState() const { return _5c90; }
    void x_2();
    void x_3();
    bool x_4();
    void x_5();

private:
    virtual ~CompactedHeap();

    u8 _8[0x5c90 - 0x8];
    s32 _5c90;
    sead::Atomic<s32> mCompactionCount;
    void* _5c98;
    u32 _5ca0;
    u8 _5ca4[0x5cb8 - 0x5ca4];
    s32 _5cb8;
    u8 _5cbc[0x5cf8 - 0x5cbc];
    sead::CriticalSection _5cf8;
    sead::CriticalSection _5d38;
    sead::CriticalSection _5d78;
    u32 _5db8;
    u32 _5dbc;
    sead::SafeString _5dc0;
};
KSYS_CHECK_SIZE_NX150(CompactedHeap, 0x5dd0);

}  // namespace ksys::res
