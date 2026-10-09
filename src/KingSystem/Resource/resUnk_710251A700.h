#pragma once

#include <container/seadRingBuffer.h>
#include <container/seadListImpl.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Resource/resUnk_71024F9D48.h"

namespace ksys::res {

// FilePathContainer-adjacent helper; vtable 0x710251a700.
class Unk_710251A700 {
public:
    Unk_710251A700();
    virtual ~Unk_710251A700();

    struct InitArg {
        u32 _0;
        sead::Heap* _8;
    };
    // Native 12B9054 allocates 0x78 bytes; BfRes1200038 / 12003D0 produce and release
    // entries in the list at +0x150, using the node at +8 and handle at +0x18.
    struct Entry {
        u32 ref_count = 0;
        u32 hash = 0;
        sead::ListNode node;
        Unk_71024F9D48 handle;
    };
    bool sub_71012B9054(const InitArg& arg);
    void* sub_71012B913C();
    void sub_71012B91B4(void* item);

private:
    sead::CriticalSection mCS;
    sead::RingBuffer<void*> mBuffer;
};
KSYS_CHECK_SIZE_NX150(Unk_710251A700, 0x60);

}  // namespace ksys::res
