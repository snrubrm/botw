#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace sead {
class Heap;
}

namespace ksys::act {
class Chemical;

// 2026-10-07: D9A1D0 constructs a 0x290-byte Node with vtable24DD490; D9A970/D9AA0C
// are its original own D1/D0. Only the prefix used by D9AA84 is recovered; do not allocate it.
class Unk_71024dd490 : public sead::hostio::Node {
public:
    struct CreateArg {
        CreateArg();
        s32 _0;
        s32 _4;
        sead::SafeString worldName;
        void* _18;
    };
    static_assert(sizeof(CreateArg) == 0x20);

    virtual ~Unk_71024dd490();
    void sub_7100D9AA84();
    void sub_7100D9AAE4();

    u8 _8[0x48 - 0x8];
    sead::CriticalSection _48;
    u8 _88[0xc8 - 0x88];
    u32 _c8;
    u8 _cc[0xd8 - 0xcc];
    // D9A384 allocates this Chemical array; D9AA84/D9AAE4 dispatch Chemical methods on it.
    sead::PtrArray<Chemical> mChemicals;
};

Unk_71024dd490* sub_7100D9A1D0(const Unk_71024dd490::CreateArg& arg, sead::Heap* heap);

}  // namespace ksys::act
