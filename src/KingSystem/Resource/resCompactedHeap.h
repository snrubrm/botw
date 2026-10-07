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

    // 0x71012b8d70 (CSV CompactedHeap::Unk2::setPointer). Placeholder type: 32 pointers. The source is taken by
    // reference (the original reloads it after every store).
    struct Unk2 {
        void setPointer(void* const& ptr);

        void* _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk2, 0x100);

    // 0x71012b5310 (CSV CompactedHeap::Unk1::setPointer): 27 Unk2 entries.
    struct Unk1 {
        void setPointer(void* const& ptr);

        Unk2 _0[27];
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x1b00);

    // 0x71012b8e74 (CSV CompactedHeap::Unk4::setPointer): same shape as Unk2 (placeholder type).
    struct Unk4 {
        void setPointer(void* const& ptr);

        void* _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk4, 0x100);

    // 0x71012b5490 (CSV agl::sdw::PrimitiveOcclusion::calcContext: a wrong auto-name; 464 B): 32 Unk4 entries.
    struct Unk3 {
        void setPointer(void* const& ptr);

        Unk4 _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk3, 0x2000);

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
