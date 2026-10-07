#pragma once

#include <container/seadRingBuffer.h>
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
    bool sub_71012B9054(const InitArg& arg);
    void* sub_71012B913C();
    void sub_71012B91B4(void* item);

private:
    struct Entry {
        u64 _0 = 0;
        void* _8 = nullptr;
        void* _10 = nullptr;
        Unk_71024F9D48 _18;
    };
    sead::CriticalSection mCS;
    sead::RingBuffer<void*> mBuffer;
};
KSYS_CHECK_SIZE_NX150(Unk_710251A700, 0x60);

}  // namespace ksys::res
