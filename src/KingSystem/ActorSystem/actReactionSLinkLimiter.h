#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Reaction emission limiter at Unk1 +0xe8, allocated as 0x2c0 bytes by 0x7100ec2fdc.
// Vtable 0x71024f02a8. Each list has a 0x28-byte node containing a 0x18-byte entry.
class Unk_71024f02a8 {
public:
    struct Entry {
        xlink2::HandleSLink handle;
        f32 distance = 0.0f;
        u32 frame = 0;
    };
    static_assert(sizeof(Entry) == 0x18);
    using EntryList = sead::ObjList<Entry>;
    struct Config {
        s32 capacity;
        u32 flags;
        f32 maxDistance;
        s32 minFrames;
        s32 fadeFrames;
    };
    static_assert(sizeof(Config) == 0x14);

    Unk_71024f02a8();
    virtual ~Unk_71024f02a8();
    void init(sead::Heap* heap);
    void calc();
    // Updates active entries and optional listener distances; declared only.
    void sub_7100EC9C3C(EntryList& list, u32 flags);
    bool sub_7100EC9D84(s32 type, const sead::Vector3f& position, bool force);
    void sub_7100ECA2A0(s32 type, const sead::Vector3f& position,
                       const xlink2::HandleSLink& handle);

private:
    /* 0x008 */ EntryList mLists[13];
    /* 0x278 */ u32 mFrame = 0;
    /* 0x280 */ sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f02a8, 0x2c0);

}  // namespace ksys::act
